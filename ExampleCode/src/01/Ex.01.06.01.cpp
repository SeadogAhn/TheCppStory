// Ex.01.06.01.cpp

#include <iostream>

using namespace std;

template <typename T>
T fnSum(T a, T b)
{
    return a + b;
}

int main()
{
    cout << "integer type summation : 5 + 3 = " << fnSum(5,3) << endl;
    cout << "floating number type summation : 3.45 + 1.23 = " << fnSum(5,3) << endl;

    return EXIT_SUCCESS;
}
