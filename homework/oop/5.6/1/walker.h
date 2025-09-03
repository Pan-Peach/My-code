#ifndef Walker_H
#define Walker_H

#include <iostream>


class Walker {
public:
    Walker() {
        money = 0;
    }
    Walker(int m) {
        money = m;
    }
    virtual ~Walker()=default;
    int getMoney() const {
        return money;
    }
    void setMoney(int m) {
        money = m;
    }
protected:
    int money;
    
};

#endif // Walker_H