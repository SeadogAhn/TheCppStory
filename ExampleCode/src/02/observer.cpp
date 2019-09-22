#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*----------------------------------------------------------------------------------
    Observer pattern
----------------------------------------------------------------------------------*/
class CObservable;
//! Observer pattern base class
class CObserver {
public:
    virtual void update(CObservable* obj) = 0;
};
//! Observer pattern observable class
class CObservable {
public:
    //! observer add
    void addObserver(CObserver* observer)
    {
        observers.push_back(observer);
    }
    //! observer remove
    void removeObserver(CObserver* observer)
    {
        observers.erase( remove( observers.begin(), observers.end(), observer) );
    }
    //! notify interface
    void notify()
    {
        for (size_t i=0; i < observers.size(); ++i) {
            observers[i]->update(this);
        }
    }

protected:
    vector<CObserver*> observers;
};

/*----------------------------------------------------------------------------------
    Figure classes
----------------------------------------------------------------------------------*/
class CFigure : public CObservable {
public:
    virtual ~CFigure() {};
    virtual void draw() = 0;
    virtual void move(int x, int y) = 0;
    virtual void resize(int w, int h) = 0;
    virtual void getLocation(int& rx, int& ry) = 0;
};

class CLine : public CFigure {
protected:
    int nX1_, nY1_, nX2_, nY2_;
public:
    CLine(int x1, int y1, int x2, int y2) : nX1_(x1), nY1_(y1), nX2_(x2), nY2_(y2) {}
    virtual void draw()
    {
        cout<<"CLine("<<nX1_<<","<<nY1_<<","<<nX2_<<","<<nY2_<<")"<< endl;
    }
    virtual void move(int x, int y)
    {
        nX1_ += x; nX2_ += x; nY1_ += y; nY2_ += y;
        notify();
    }
    virtual void resize(int w, int h)
    {
        nX2_ += w; nY2_ += h;
        notify();
    }
    virtual void getLocation(int& rx, int& ry)
    {
        rx = nX1_; ry = nY1_;
    }
};

class CRectangle : public CFigure {
protected:
    int nX_, nY_, nWidth_, nHeight_;
public:
    CRectangle(int x, int y, int w, int h) : nX_(x), nY_(y), nWidth_(w), nHeight_(h) {}
    virtual void draw()
    {
        cout<<"CRectangle("<<nX_<<","<<nY_<<","<<nWidth_<<","<<nHeight_<<")"<<endl;
    }
    virtual void move(int x, int y)
    {
        nX_ += x; nY_ += y;
        notify();
    }
    virtual void resize(int w, int h)
    {
        nWidth_ += w; nHeight_ += h;
        notify();
    }
    virtual void getLocation(int& rx, int& ry)
    {
        rx = nX_; ry = nY_;
    }
};

class CText : public CFigure {
protected:
    int nX_, nY_;
    string str_;
public:
    CText(int x, int y, const string& s) : nX_(x), nY_(y), str_(s) {}
    virtual void draw()
    {
        cout<<"CText("<< nX_<<","<< nY_<<","<< str_<<")"<< endl;
    }
    virtual void move(int x, int y)
    {
        nX_ += x; nY_ += y;
        notify();
    }
    virtual void resize(int /*w*/, int /*h*/) {}
    virtual void getLocation(int& rx, int& ry)
    {
        rx = nX_; ry = nY_;
    }
};

class CRoundRect : public CRectangle {
protected:
    int nRound_;
public:
    CRoundRect(int x, int y, int w, int h, int r) : CRectangle(x,y,w,h) { nRound_ = r; }
    virtual void draw()
    {
        cout<<"CRoundRect("<< nX_<<","<< nY_<<","<< nWidth_<<","<< nHeight_<<","<< nRound_<<")"<< endl;
    }
};

/*----------------------------------------------------------------------------------
    Docorate pattern
----------------------------------------------------------------------------------*/
class CDecorator : public CFigure, public CObserver {
protected:
    CFigure* pFigure_;
    int nX_, nY_;
public:
    void setFigure(CFigure* f)
    {
        pFigure_ = f;
        pFigure_->getLocation(nX_, nY_);
        pFigure_->addObserver(this);
    }
    virtual void draw() {}
    virtual void move(int x, int y)
    {
        pFigure_->move(x, y);
    }
    virtual void resize(int w, int h)
    {
        pFigure_->resize(w, h);
    }
    virtual void getLocation(int& rx, int& ry)
    {
        rx = nX_; ry = nY_;
    }
    virtual void update(CObservable* /*obj*/)
    {
        pFigure_->getLocation(nX_, nY_);
        notify();
    }
};

class CShadowDecorator : public CDecorator {
public:
    virtual void draw()
    {
        cout<<"Shadow("<< nX_<<","<< nY_<<")";
        pFigure_->draw();
    }
};

class CHandleDecorator : public CDecorator {
public:
    virtual void draw()
    {
        cout<<"Handle("<< nX_<<","<< nY_<<")";
        pFigure_->draw();
    }
};


/*----------------------------------------------------------------------------------
    Client Code
----------------------------------------------------------------------------------*/
struct CDeleteObject{
    template< typename T >
    void operator()(const T* ptr) const
    {
        delete ptr;
    }
};

vector<CFigure*> FigureContainer;

void fnAddDecorator(const string& str, CDecorator* d) {
    int n = atoi(str.substr(str.find(' ')+1).c_str());
    if (n < 0 || n > static_cast<int>(FigureContainer.size())) return;
    CFigure* f = FigureContainer[n];
    d->setFigure(f);
    FigureContainer[n] = d;
}

void fnMove(const string& str) {
    int n = atoi(str.substr(str.find(' ')+1).c_str());
    if (n < 0 || n > static_cast<int>(FigureContainer.size())) return;
    CFigure* f = FigureContainer[n];
    f->move(10, 10);
}

int main() {
    string str;

    FigureContainer.push_back(new CRectangle(0, 0, 100, 50));
    FigureContainer.push_back(new CLine(200, 0, 300, 50));
    FigureContainer.push_back(new CText(400, 0, "Hello"));
    FigureContainer.push_back(new CRoundRect(500, 0, 600, 50, 10));

    for (;;) {
        printf("\n객체목록\n");
        for (size_t i=0; i < FigureContainer.size(); ++i) {
            printf("%d: ", i);
            FigureContainer[i]->draw();
        }
        printf("\nShadow decorator : s <객체번호>");
        printf("\nHandle decorator : h <객체번호>");
        printf("\nMove : m <객체번호>");
        printf("\n종료 : q");
        printf("\n? ");
        getline( cin, str );
        switch (toupper(str[0])) {
        case 'S': fnAddDecorator(str, new CShadowDecorator); break;
        case 'H': fnAddDecorator(str, new CHandleDecorator); break;
        case 'M': fnMove(str); break;
        case 'Q': goto done;
        }
    }
done:
    for_each(FigureContainer.begin(), FigureContainer.end(), CDeleteObject() );

    return EXIT_SUCCESS;
}
