// Ex.00.03.01.cpp

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <typeinfo>

using namespace std;

#define SAMPLE_D_FUNC_INFO   cout << __FUNCTION__ << ':' << __LINE__ << ':' << __DATE__ << ' ' << __TIME__ << endl

template <typename Container>
size_t fnPrintContainer(const Container& c, const char* str = "")
{
#ifdef _DEBUG
    SAMPLE_D_FUNC_INFO;
#endif
    cout << str << ':';
    for (const auto& val : c) {
        cout << val << ' ';
    }
    cout << endl;
    return c.size();
}

class DataType {
public:
    //! defalut constructor
    explicit DataType(int n = 0, const string& str = "") : nUserID_(n), strUserName_(str) {}
    //! member variables to string
    const string to_string() const
    {
        ostringstream oss;
        oss << nUserID_ << ',' << strUserName_;
        return oss.str();
    }

private:
    int nUserID_;       ///< User's ID
    string strUserName_;///< User's name
};

// operator<< overload for putting the DataType to ostream
std::ostream& operator<<(ostream& os, const DataType& data)
{
    os << data.to_string();
    return os;
}

int main()
{
    // list of int
    list<int> listInt = { 0,1,2,3,4,5,6,7,8,9 };
    // vector of int
    vector<int> vecInt = { 0,1,2,3,4,5,6,7,8,9 };
    // vector of DataType
    vector<DataType> vecData;
    vecData.emplace_back(1, "Steve");
    vecData.emplace_back(2, "Robert");
    vecData.emplace_back(3, "Michael");

    fnPrintContainer(listInt, typeid(listInt).name());
    fnPrintContainer(vecInt, typeid(vecInt).name());
    fnPrintContainer(vecData, typeid(vecData).name());

    return EXIT_SUCCESS;
}
