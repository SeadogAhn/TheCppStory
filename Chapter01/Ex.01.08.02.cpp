//Ex.01.08.02.cpp

#include <iostream>
#include <string>
#include <typeinfo>
#include <sstream>

using namespace std;

//! Tire
class Tire {
public:
    Tire(){}
    ~Tire(){}
    void setType(const string& type) { type_ = type; }
    const string& getType() const { return type_; }
private:
    string type_;
};

//! Engine
class Engine {
public:
    Engine(){}
    ~Engine(){}
    void setType(const string& type) { type_ = type; }
    const string& getType() const { return type_; }
private:
    string type_;
};

//! bass class of Car
class Car {
public:
    Car(){}
    virtual ~Car(){}
    //pure virtual member function
    virtual void run() = 0;
    virtual void stop() = 0;

    void info()
    {
        cout << "Car    : " << typeid(*this).name() << endl;
        cout << "Number : " << strPlateNumber_ << endl;
        cout << "Tire   : " << tire_.getType() << endl;
        cout << "Engine : " << engine_.getType() << endl;
    }

protected:
    Tire tire_;
    Engine engine_;
    string strPlateNumber_;
};

class LuxuryCar : public Car {
public:
    LuxuryCar():Car()   {}
    virtual ~LuxuryCar(){}
    virtual void run()  { cout << " Running...." << typeid(*this).name() << endl; }
    virtual void stop() { cout << " Stopping..." << typeid(*this).name() << endl; }
};

class SUV : public Car {
public:
    SUV():Car(){};
    virtual ~SUV(){}
    virtual void run() { cout << " Running...." << typeid(*this).name() << endl; }
    virtual void stop(){ cout << " Stopping..." << typeid(*this).name() << endl; }
};

class S600 : public LuxuryCar {
public:
    S600(const string& PlatNumber = ""):LuxuryCar(){ init(PlatNumber); }
    ~S600(){}
    void run()      { cout << " Running...." << typeid(*this).name() << endl; }
    void stop()     { cout << " Stopping..." << typeid(*this).name() << endl; }
    void driveAuto(){ cout << " Atonomous.." << typeid(*this).name() << endl; }

private:
    void init(const string& PlatNumber = "")
    {
        strPlateNumber_ = PlatNumber;
        tire_.setType("275/35R20");
        engine_.setType("4.0L V8");
    }
};

class RX450h : public SUV {
public:
    explicit RX450h(const string& PlatNumber = ""):SUV() { init(PlatNumber); }
    void run()       { cout << " Running...." << typeid(*this).name() << endl; }
    void stop()      { cout << " Stopping..." << typeid(*this).name() << endl; }
    void useBattery(){ cout << " Using BAT.." << typeid(*this).name() << endl; }

private:
    void init(const string& PlatNumber = "")
    {
        strPlateNumber_ = PlatNumber;
        tire_.setType("235/55R20");
        engine_.setType("3.5L V6");
    }
};


/////////////////////////////////////////////////////////////////////////////
void CarInfo( Car* car )
{
    car->info();
}

int main()
{
    Car* WifeCar = new RX450h("ABC123");
    CarInfo( WifeCar );
    WifeCar->run();
    dynamic_cast<RX450h*>(WifeCar)->useBattery();
    WifeCar->stop();

    Car* MyCar = new S600("XYZ007");
    CarInfo( MyCar );
    MyCar->run();
    dynamic_cast<S600*>(MyCar)->driveAuto();
    MyCar->stop();

    delete WifeCar;
    delete MyCar;

    return 0;
}

