/*-----------------------------------------------------------------------------------------
 * finename    : dpa.cpp
 * eng'r name  : Jeong-il Ahn(raon_pgm@naver.com)
 * date        : 1998 . 2. 2.
 * title       : precision analysis
 * purpose     : The precision of floating point format analysis
 * description : - wikipedia.org -
                 In computing, double precision is a computer numbering format that
                 occupies two storage locations in computer memory at address and
                 address+1.
                 A double precision number, sometimes simply called a double, may be
                 defined to be an integer, fixed point, or floating point.

                 Modern computers with 32-bit stores (single precision) provide
                 64-bit double precision.
                 Double precision floating point is an IEEE 754 standard for
                 encoding floating point numbers that uses 8 bytes.
 * reference   : http://en.wikipedia.org/wiki/Double_precision
 * environment : system   : intel cpu 32bit windows XP
                 compiler : g++ -3.4.5 (mingw32) || gnu g++
 * compute formula 
   formula is to compute double precision : -1^sign * 2^(exponent-exponent bias) * 1.mantissa

    @ single precision

    sign
    |exponent (8 bits)
    ||      |fraction (23 bits)
    ||      ||                     |
    *########&&&&&&&&&&&&&&&&&&&&&&&
    |       |                      |
    31      23                     0


    @ double precision

    sign
    |exponent (11 bits)
    ||         |fraction (52 bits)
    ||         ||                                                  |
    *###########&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    |          |                                                   |
    63         52                                                  0

 *----------------------------------------------------------------------------------------*/

#include <iostream>
#include <iomanip>
#include <ios>
#include <stdexcept>
#include <string>
#include <bitset>
#include <cmath>

using namespace std;

//! global variables
// size of double type = 8byte
const size_t sizeVar = sizeof(double);
// bit memory size
const size_t sizeBitset = sizeVar * 8;
const size_t sizeExponent = 11;
const size_t sizeMantissa = 52;
// exponent bias = 1023
const unsigned long ulExponentBias = 1023;

// get mantissa from bitset<sizeBitset>
double fnMantissa( const bitset<sizeBitset> &b );
// get exponent from bitset<sizeBitset>
double fnExponent( const bitset<sizeBitset> &b );

void usage()
{
    cout << " usage : dpa NUM" << endl;
    cout << "\n        NUM = floating point number" << endl;
    exit(EXIT_FAILURE);
}

int main( int argc, char **argv )
{
    if( argc != 2 ){
        usage();
    }

    try {
        //argument is double type
        double dblNumber = atof(argv[1]);

        double dblSign;         // sign     : 1bit
        double dblExponent;     // exponent : 2^(exponent-exponent bias)
        double dblSignificand;  // mantissa : 1.mantissa 
        double dblResult;       // double precision : -1^sign * 2^(exponent-exponent bias) * 1.mantissa

        dblSign = dblExponent = dblSignificand = dblResult = 0.;

        bitset< sizeBitset > bit;  //bitset container

        // floating point type의 경우 if문으로 == , != 를 비교하는 것은 오류가 생길 수 있지만,
        // Input argument 값에 대한 다른 연산이 없으며,
        // 입력 값이 잘못되었을 경우 atof는 0. 을 return 하므로 확인하고 처리한다.
        if ( dblNumber != 0. ) {
            //double type을 각 1byte씩 잘라 char type으로 casting하고 bitset에 입력
            for( int i = sizeVar-1 ; i >= 0 ; --i ){
                bit |= bitset<sizeBitset>( ( reinterpret_cast< unsigned char* >(&dblNumber) )[i] );
                if( i != 0 ){
                    bit <<= 8;
                }
            }

            dblSign         = bit[sizeBitset-1] ? -1. : 1.;
            dblExponent     = fnExponent( bit );
            dblSignificand  = 1.+fnMantissa( bit );
            dblResult       = dblSign * dblExponent * dblSignificand;
        }

        // bitset을 구분별로 출력하기 위해 string에 대입
        string strBitSet = bit.to_string<char,char_traits<char>,allocator<char> >();

        // print to standard output
        // stream precision set
        streamsize prec = cout.precision();
        cout << endl
             // single precision 의 경우 신뢰할 수 있는 수준은 소수점 이하 9자리 정도이고,
             // double precision 의 경우는 소수점 이하 15자리 정도이다.
             // 오차를 확인하고자 할 경우 precision set을 변경하면 된다.
             << setprecision(15)
             << "Input value : " << dec << dblNumber << endl << endl
             // bits : 10000 이라면 string의 경우 1의 position은 [0] 이지만
             // bitset의 경우 1의 position은 bit order기준으로 [4] 가 된다.
             // access operator 사용이 반대로 되므로 주의가 필요하다.
             << "Double precision bit data " << endl
             << "sign        : " << strBitSet[0] << endl
             << "exponent    : " << strBitSet.substr(1,sizeExponent) << endl
             << "significand : " << strBitSet.substr(sizeExponent+1) << endl << endl
             << "Compute bit data" << endl
             << "double precision : -1^sign * 2^(exponent-exponent bias) * 1.mantissa" << endl
             << "compute double   : "   << dblSign << " * " << dblExponent << " * " << dblSignificand << endl
             << "                 = "   << dblResult << endl
             << setprecision(prec);
    }
    catch ( const exception& error ) {
        cerr << error.what() << endl;
        exit ( EXIT_FAILURE );
    }
    catch (...) {
        cerr << "Unknown error caught, Process has been halted." << endl;
        exit ( EXIT_FAILURE );
    }

    return ( EXIT_SUCCESS );
}

double fnExponent( const bitset<sizeBitset> &b )
{
    string str = b.to_string< char,char_traits<char>,allocator<char> >();
    long lValue = bitset<sizeExponent>(str.substr(1,sizeExponent)).to_ulong() - ulExponentBias;

    return (
              lValue < 0
            ? 1. / pow( 2, static_cast<double>( abs(lValue) ) )  
            : pow( 2, static_cast<double>( lValue ) )
           );
}

double fnMantissa( const bitset<sizeBitset> &b )
{
    double dblMantissa = 0;
    __int64 n64 = 2;
    for( int sz = sizeMantissa-1 ; sz >= 0 ; --sz ){
        dblMantissa += ( b[sz] * ( 1. / n64 ) );
        n64 <<= 1;
    }

    return dblMantissa;
}
