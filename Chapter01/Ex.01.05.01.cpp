//!Ex.01.05.01.cpp

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename Container>
void print(const Container& c)
{
    typedef typename Container::value_type value_type;
    copy(cbegin(c), cend(c), ostream_iterator<value_type>(cout, " "));
    cout << endl;
}

int main(int argc, char *argv[])
{
    string str = "Hello world";
    print(str);

    vector<string> vecStr {"abc", "def", "ghi", "jkl" };
    print(vecStr);

    return EXIT_SUCCESS;
}
