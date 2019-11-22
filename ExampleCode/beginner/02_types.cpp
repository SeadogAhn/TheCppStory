#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <complex>
#include <typeinfo>
#include <algorithm>

using namespace std;

int main()
{
    bool Bool{true};        ///< boolean
    short Short{2};         ///< short
    int Integer{4};         ///< int
    long Long{4};           ///< long
    float Float{ 2.5 };     ///< single floating number
    double Double{ 3.5 };   ///< double floating number
    complex<double> Complex{ 5.3, 7.2 };///< double type complex
    pair<int, double> Pair(Integer, Double);
    tuple<int, float> Tuple(Integer, Float);

    cout << boolalpha << Bool << ',' << &Bool << ',' << sizeof(Bool) << endl;
    cout << Short << ',' << &Short << ',' << sizeof(Short) << endl;
    cout << Integer << ',' << &Integer << ',' << sizeof(Integer) << endl;
    cout << Long << ',' << &Long << ',' << sizeof(Long) << endl;
    cout << Float << ',' << &Float << ',' << sizeof(Float) << endl;
    cout << Double << ',' << &Double << ',' << sizeof(Double) << endl;
    cout << Complex << ',' << &Complex << ',' << sizeof(Complex) << endl;
    cout << /*Pair << ',' <<*/ &Pair << ',' << sizeof(Pair) << endl;
    cout << /*Tuple << ',' <<*/ &Tuple << ',' << sizeof(Tuple) << endl;

    int Array[5] = { 0, };              ///< array of int
    int* Pointer = Array;               ///< pointer of int
    int* PointerToArray[5] = { 0, };    ///< array of pointer of int
    int(*ArrayPointer)[5] = &Array;     ///< array of pointer of int

    cout << Array << ',' << &Array << ',' << sizeof(Array) << endl;
    cout << Pointer << ',' << &Pointer << ',' << sizeof(Pointer) << endl;
    cout << PointerToArray << ',' << &PointerToArray << ',' << sizeof(PointerToArray) << endl;
    cout << ArrayPointer << ',' << &ArrayPointer << ',' << sizeof(ArrayPointer) << endl;

    char Char {'c'};                    ///< char
    const char* szChar {"Character"};   ///< const char
    const char* const & rszChar {szChar}; ///< reference of pointer of const char
    string String {"String"};            ///< string
    string& ReferenceOfString {String}; ///< reference of string

    cout << Char << ',' << (void*)&Char << ',' << sizeof(Char) << endl;
    cout << szChar << ',' << &szChar << ',' << sizeof(szChar) << endl;
    cout << rszChar << ',' << &rszChar << ',' << sizeof(rszChar) << endl;
    cout << String << ',' << &String << ',' << sizeof(String) << endl;
    cout << ReferenceOfString << ',' << &ReferenceOfString << ',' << sizeof(ReferenceOfString) << endl;

    //! vector container
    vector<int> vecInteger = { 0, 1, 2, 3, 4, 5 };
    cout << typeid(vecInteger).name() << ',' << &vecInteger << ',' << sizeof(vecInteger) << endl;

    for (const auto& Val : vecInteger) {
        cout << Val << ' ';
    }
    cout << endl;

    //! map container
    map<int, vector<int> > mapIntVector;
    mapIntVector.insert(make_pair(1, vecInteger));
    mapIntVector.insert(make_pair(2, vecInteger));
    mapIntVector.insert(make_pair(3, vecInteger));

    cout << typeid(mapIntVector).name() << ',' << &mapIntVector << ',' << sizeof(mapIntVector) << endl;

    for (const auto& KeyVal : mapIntVector) {
        cout << KeyVal.first << endl;
        cout << typeid(KeyVal.first).name() << ',' << &KeyVal.first << ',' << sizeof(KeyVal.first) << endl;
        cout << typeid(KeyVal.second).name() << ',' << &KeyVal.second << ',' << sizeof(KeyVal.second) << endl;

        for (const auto& Val : KeyVal.second) {
            cout << Val << ' ';
        }
        cout << endl;
    }
}
