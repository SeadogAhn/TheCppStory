#include <iostream>

using namespace std;

class Complex
{
public:
    Complex() : real_{0.}, img_{0.} {}
    Complex(double r, double i) : real_{r}, img_{i} {}
    Complex(const Complex& c) : real_{c.real_}, img_{c.img_} {}

    void operator+=(const Complex& c)
    {
        real_ += c.real_;
        img_ += c.img_;
    }

    friend ostream& operator<<(ostream& os, const Complex& c);

private:
    double real_;
    double img_;
};

ostream& operator<<(ostream& os, const Complex& c)
{
    os << '(' << c.real_ << ',' << c.img_ << ')';
    return os;
}

Complex operator+(const Complex& c1, const Complex& c2)
{
    Complex temp(c1);
    temp += c2;
    return temp;
}

int main(int argc, char *argv[])
{
    Complex c1(2,3), c2(3,5), c3;
    c3 = c1 + c2;
    cout << c3 << endl;
    cout << c1 + c2 << endl;
    return 0;
}
