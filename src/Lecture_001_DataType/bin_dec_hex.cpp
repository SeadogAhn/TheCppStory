#include <iostream>
#include <string>
#include <bitset>
#include <cstdio>
#include <iomanip>

using namespace std;

int main()
{
    double first = 1.0;
    double second = 1.00001;
    double result = second - first;

    /*types size*/
    printf("Type size of double : %d , Type size of character : %d\n\n", sizeof(double), sizeof(char));

    /*Integer variable n's infomation*/
    printf("Assigne address of result  : %p  value DEC : %lf\n\n", &result, result);

    string strBinary;

    /*type casting from integer to char, it's infomation*/
    for( size_t i = sizeof(double) ; i > 0 ; --i ){
        printf("char point[%d] address : %p  value DEC : %3d , HEX : %2x , BIN : ",
            i,
            &((unsigned char*)&result)[i],
            ((unsigned char*)&result)[i],
            ((unsigned char*)&result)[i]
        );
        std::bitset< 8 > bit = ((unsigned char*)&result)[i];
        cout << bit << endl;
        
        strBinary += bit.to_string<char,char_traits<char>,allocator<char> >();
   }
   cout << setprecision(20);
   cout << dec << "double = " << result << "\nbin = " << strBinary << endl;

   return(0);
}

/*
||         ||                                                  |
00         10        1         2         3         4         5
1123456789011234567890123456789012345678901234567890123456789012

0000000000000000111001001000100010110101111110001110010000111110

1100000000111110111001001111100010110101100010001110010000000000

*/
