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
    printf("Msg:%s, Type:%s, Size :%u, Values:", str, typeid(arr).name(), arr.size());
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
    // this constructor would be worked, explicit Array(size_type sz, const value_type& val = T())
    // Q1. why it is to use "explicit"? if there is no "explict", what happend?
    Array<double> arr1(5);
    // Q2, which constructor will be work?
    Array<double> arr2 = {0,1,2,3,4,5,6,7,8,9};

    print(arr1, "arr1");
    print(arr2, "arr2");
    SPLIT_LINE
    // Q3. how to work, could you explaine that?
    arr1 = arr2;
    print(arr1, "arr1");
    SPLIT_LINE
    // make string container
    Array<string> arrStr = {"ABC", "DEF", "GHI"};
    print(arrStr, "arrStr");
    SPLIT_LINE
    // Q4. if you remove the annotation symbol below, it'll be occured error, why?
    // Q5. can you modify to assign this? is it right way?
    //arr1 = arrStr;
    // Q6. Please provide random accesseble operator[], like code below.
    cout << arr1[1] << ',' << arr2[1] << ',' << arrStr[1] << endl;
    arr1[2] = 10.8;
    print(arr1[2], "arr1[2]");
    print(arr1, "arr1");
    SPLIT_LINE
    // Q7. And after add random accesseble operator, do code below, is it work right?
    // Q8. if it occoured error, why? what do you have to do?
    const decltype(arr1) arrConst(arr1);
    print(arrConst[2], "arrConst[2]");
    SPLIT_LINE
    // test move constructor
    decltype(arr1) arr3(move(arr1));
    print(arr1, "arr1");
    print(arr3, "arr3");
    SPLIT_LINE
    // Q9. What happened the move assign operator is working?
    arr3 = move(arr2);
    print(arr2, "arr2");
    print(arr3, "arr3");
    SPLIT_LINE

    return EXIT_SUCCESS;
}
