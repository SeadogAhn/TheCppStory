// Ex.01.08.01.cpp

#include <iostream>
#include <vector>
#include <map>
#include <typeinfo>
#include <memory>

using namespace std;

#define TYPE_INFO cout << typeid(*this).name() << "::" << __FUNCTION__ << endl

class Base {
public:
	Base() { TYPE_INFO;	}
	virtual ~Base() { TYPE_INFO; }
    virtual void whoami() = 0;
};

class DerivedA : public Base {
public:
	DerivedA() { TYPE_INFO;	}
	~DerivedA() { TYPE_INFO; }
    void whoami() override { TYPE_INFO; }
};

class DerivedB : public Base {
public:
	DerivedB() { TYPE_INFO;	}
	~DerivedB() { TYPE_INFO; }
    void whoami() override { TYPE_INFO; }
};

int main()
{
    //! vector of pointer to Base
	vector<shared_ptr<Base>> vecBase;
    //! push back to vector
    vecBase.push_back(make_shared<DerivedA>());
	vecBase.push_back(make_shared<DerivedB>());
    //! loop
    for (auto& val : vecBase) {
        val->whoami();
    }

    //! map of key is int and value is pointer to Base
	map< int, shared_ptr<Base>>  mapIntBase;
    //! insert key and value
	mapIntBase[1] = make_shared<DerivedA>();
	mapIntBase[2] = make_shared<DerivedB>();
    //! loop
    for (auto& val : mapIntBase) {
        val.second->whoami();
    }

	return EXIT_SUCCESS;
}
