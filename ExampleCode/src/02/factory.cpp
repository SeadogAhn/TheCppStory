#include <iostream>

using namespace std;

class Car{
public:
    Car() = default;
    virtual ~Car() = default;
    virtual void drive() = 0;
};

class Lamborghini : public Car{
public:
    void drive()
    { cout << "Running Lamborghini!!!" << endl; }
};

class Porsche : public Car{
public:
    void drive()
    { cout << "Running Porsche!!!" << endl; }
};


class CreatorCar{
public :
    CreatorCar() : pcar_(0) {}
    virtual ~CreatorCar(){ delete pcar_; }
    void NewCar()
    {
        if( pcar_ ) delete pcar_;
        pcar_ = CreateCar();
    }
    Car* getCar() const { return pcar_; }
protected:
    virtual Car* CreateCar() = 0;
private:
    Car* pcar_;
};

template< typename CarType >
class ConcreateCreatorCar : public CreatorCar{
protected:
    Car* CreateCar()
    {
        return new CarType;
    }
};


int main()
{
    ConcreateCreatorCar< Porsche > car;
    car.NewCar();
    car.getCar()->drive();

    return EXIT_SUCCESS;
}
