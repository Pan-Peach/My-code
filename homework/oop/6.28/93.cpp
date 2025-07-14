#include <iostream>
using namespace std;

class A {

public:

      A (int n=1):mVal(n)                       { cout<<1; }

      A (const A& rhs):mVal(rhs.mVal)  { cout<<2;}

      A&operator=(const A& )              { cout<<3; return *this;}

      ~A( )                                              {  }

      int  mVal;

};

class B:public A {

public:

      B( )                   { cout<<4; }

      B(const B&)     { cout<<5;}

      B&operator=(const B& )  { cout<<6; return *this;}

};

int main( ) {

    B  b1;

    B b2(b1);

    b1 = b2;

}