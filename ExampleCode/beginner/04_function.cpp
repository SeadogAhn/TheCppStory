#include <iostream>

using namespace std;

void func()
{
    printf("%s():", __FUNCTION__);
    cout << "do something" << endl;
}

int func(int n)
{
    printf("%s(%d):", __FUNCTION__, n);
    cout << "do something" << endl;
    return n;
}

int main(int argc, char** argv)
{
    printf("%s(%d,%s)\n", __FUNCTION__, argc, *argv);
    func();
    cout << func(10) << endl;

    return EXIT_SUCCESS;
}
