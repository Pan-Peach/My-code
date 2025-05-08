#ifndef Thief_H
#define Thief_H

#include<bits/stdc++.h>
#include "walker.h" // Ensure this file contains the full definition of Walker
using namespace std;

// class Walker; // Forward declaration

class Thief:public Walker {
public:
    Thief():Walker(){};
    Thief(int m):Walker(m){};
    virtual ~Thief()=default;
    void steal(Walker& w) {
        cout << "Thief is stealing!" << endl;
        money += w.getMoney();
        w.setMoney(0); // Use the setter method to modify money
    }

};

#endif // Thief_H
