#pragma once
#include <string>
using namespace std;

class Item {
protected:
    int id;
public:
    Item() : id(0) {}
    Item(int id) : id(id) {}
    virtual ~Item() = default;
    
    virtual string serialize() = 0;
    virtual void deserialize(string line) = 0;
    virtual void display() const = 0;

    virtual int getId() const { return id; }
    virtual void setId(int newId) { id = newId; }
};