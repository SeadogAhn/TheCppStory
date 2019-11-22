#include "Array.hpp"

#include <iostream>
#include <typeinfo>
#include <iterator>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;

#define SPLIT_LINE cout << string(80, '-') << endl;

template<typename T>
void fnPrint(const Array<T>& arr, const char* str = "")
{
    printf("Msg:%s, Type:%s, Size :%u, Values:", str, typeid(arr).name(), arr.size());
    copy(arr.begin(), arr.end(), ostream_iterator<T>(cout, " "));
    cout << endl;
}

template<typename T>
void fnPrint(const T& val, const char* str = "")
{
    printf("Msg:%s, Type:%s, Value:", str, typeid(val).name());
    cout << val << endl;
}

int main()
{
    Array<double> arr1(5);
    Array<double> arr2 = {0,1,2,3,4,5,6,7,8,9};

    fnPrint(arr1, "arr1");
    fnPrint(arr2, "arr2");
    SPLIT_LINE

    arr1 = arr2;
    fnPrint(arr1, "arr1");
    SPLIT_LINE

    Array<string> arrStr = {"ABC", "DEF", "GHI"};
    fnPrint(arrStr, "arrStr");
    SPLIT_LINE

    cout << arr1[1] << ',' << arr2[1] << ',' << arrStr[1] << endl;
    arr1[2] = 10.8;
    arr1[5] = 22.5;
    fnPrint(arr1[2], "arr1[2]");
    fnPrint(arr1, "arr1");
    SPLIT_LINE

    const decltype(arr1) arrConst(arr1);
    fnPrint(arrConst[2], "arrConst[2]");
    SPLIT_LINE

    decltype(arr1) arr3(move(arr1));
    fnPrint(arr1, "arr1");
    fnPrint(arr3, "arr3");
    SPLIT_LINE

    arr3 = move(arr2);
    fnPrint(arr2, "arr2");
    fnPrint(arr3, "arr3");
    SPLIT_LINE

    return EXIT_SUCCESS;
}
