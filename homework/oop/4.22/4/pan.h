
#ifndef Pan_H
#define Pan_H
#include<iostream>
using namespace std;
class pan{
    public:
    void write(){
        cout<<"pan writing"<<endl;
    }
    private:

};

class linkpan:pan{
    public:
    void write(){
        cout<<"link pan writring"<<endl;
    }
};
#endif