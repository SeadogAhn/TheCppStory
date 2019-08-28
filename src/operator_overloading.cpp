#include <iostream>
#include <sstream>

class Point {
public:
    // type definitions
    using value_type = int;

    // constructor overloading
    Point(int x=0, int y=0) : x_(x), y_(y)
    {
    }
    // destructor
    ~Point() = default;
    // copy constructor
    Point(const Point& pnt) = default;
    // assignment opeartor
    Point& operator=(const Point& pnt) = default;
    // move constructor
    Point(Point&& pnt) = default;
    // move assignment opeartor
    Point& operator=(Point&& pnt) = delete;
    // Point to string
    const std::string str() const
    {
        std::ostringstream oss;
        oss << '(' << x_ << ',' << y_ << ')';
        return oss.str();
    }
    // prefix increment operator, ++pnt
    Point& operator++()
    {
        ++x_;
        ++y_;
        return *this;
    }
    // postfix increment operator, pnt++
    const Point operator++(int)
    {
        Point old(*this);
        ++*this;
        return old;
    }
    // prefix decrement operator, --pnt
    Point& operator--()
    {
        --x_;
        --y_;
        return *this;
    }
    // postfix decrement operator, pnt--
    const Point operator--(int)
    {
        Point old(*this);
        --*this;
        return old;
    }
    // assignment operator with addition, pnt += pnt
    Point& operator+=(const Point& pnt)
    {
        x_ += pnt.x_;
        y_ += pnt.y_;
        return *this;
    }
    // assignment operator with subtraction, pnt -= pnt
    Point& operator-=(const Point& pnt)
    {
        x_ -= pnt.x_;
        y_ -= pnt.y_;
        return *this;
    }

private:
    value_type x_;
    value_type y_;
};

std::ostream & operator<<( std::ostream &os, const Point &p )
{
    os << p.str();
    return os;
}

const Point operator+(const Point& pnt1, const Point& pnt2)
{
    Point pnt(pnt1);
    pnt += pnt2;
    return pnt;
}

const Point operator-(const Point& pnt1, const Point& pnt2)
{
    Point pnt(pnt1);
    pnt -= pnt2;
    return pnt;
}

///////////////////////////////////////////////////////////////////////////////
// g++ -std=c++1y -o xxx xxx.cpp
///////////////////////////////////////////////////////////////////////////////

using namespace std;

#define SPLIT_LINE cout << string(80,'-') << endl;

int main()
{
    // define p1 and p2 of Point type
    Point p1(1,2);
    Point p2(5,4);
    cout << "p1 :" << p1 << endl;
    cout << "p2 :" << p2 << endl;

    SPLIT_LINE
    // Q1. What is different between increment and decrement operators?
    cout << "++p1 :" << ++p1 << endl;
    cout << "--p1 :" << --p1 << endl;
    cout << "p2++ :" << p2++ << endl;
    cout << "p2-- :" << p2-- << endl;

    SPLIT_LINE
    cout << "p1 :" << p1 << endl;
    cout << "p2 :" << p2 << endl;

    SPLIT_LINE
    // Q2. it'll be occured compile time error, WHY?
    // cout << "p1++++ :" << p1++++ << endl;
    // but it'll be worked, WHY???
    cout << "p1 :" << p1 << endl;
    cout << "++++p1 :" << ++++p1 << endl;

    // and how about integer
    SPLIT_LINE
    int n = 0;
    // Q3. it'll be occured compile time error, WHY?
    // cout << "n++++ :" << n++++ << endl;
    // but it'll be worked, WHY???
    cout << "++++n :" << ++++n << endl;

    SPLIT_LINE
    cout << "p1 :" << p1 << endl;
    cout << "p2 :" << p2 << endl;

    // deinfe p3 of Point type
    Point p3(p1);

    SPLIT_LINE
    cout << "p3 :" << p3 << endl;
    p3 = p1 + p2;
    cout << "p3 = p1 + p2 :" << p3 << endl;

    // Q4. it'll be worked, WHY???
    Point p4(move(p1));
    // Q5. it'll be occured compile time error, WHY???
    // p1 = move(p2);

    return EXIT_SUCCESS;
}
