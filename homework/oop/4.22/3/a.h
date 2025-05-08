

#ifndef CA
#define CA
#include<iostream>
using namespace std;

class A {
public:
void Display() const;
// {
//            cout<<"The argment is NULL"<<endl;
//     }

void Display(const char * str) const 
{
           cout<<"The argment is "<<str<<endl;
    }
void OtherFunc() 
{
    }
};

void A::Display() const{
    cout<<"The argment is NULL"<<endl;
}

#endif