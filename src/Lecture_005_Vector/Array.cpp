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
void print(const Array<T>& arr, const char* str = "")
{
    printf("Msg:%s, Type:%s, Size :%llu, Values:", str, typeid(arr).name(), arr.size());
    copy(arr.begin(), arr.end(), ostream_iterator<T>(cout, " "));
    cout << endl;
}

template<typename T>
void print(const T& val, const char* str = "")
{
    printf("Msg:%s, Type:%s, Value:", str, typeid(val).name());
    cout << val << endl;
}

int main()
{
    Array<double> arr1(5);
    Array<double> arr2 = {0,1,2,3,4,5,6,7,8,9};

    print(arr1, "arr1");
    print(arr2, "arr2");
    SPLIT_LINE

    arr1 = arr2;
    print(arr1, "arr1");
    SPLIT_LINE

    Array<string> arrStr = {"ABC", "DEF", "GHI"};
    print(arrStr, "arrStr");
    SPLIT_LINE

    cout << arr1[1] << ',' << arr2[1] << ',' << arrStr[1] << endl;
    arr1[2] = 10.8;
    print(arr1[2], "arr1[2]");
    print(arr1, "arr1");
    SPLIT_LINE

    const decltype(arr1) arrConst(arr1);
    print(arrConst[2], "arrConst[2]");
    SPLIT_LINE

    decltype(arr1) arr3(move(arr1));
    print(arr1, "arr1");
    print(arr3, "arr3");
    SPLIT_LINE

    arr3 = move(arr2);
    print(arr2, "arr2");
    print(arr3, "arr3");
    SPLIT_LINE

    return EXIT_SUCCESS;
}
