#pragma once
#include <string>
#include "Item.h"

using namespace std;

class User:public Item {
protected:
    string account;
    string password;
public:
    virtual string serialize() = 0;
    virtual void deserialize(string line) = 0;

    User() = default;
    User(const string& acc, const string& pwd) : account(acc), password(pwd) {}
    virtual ~User() = default;
    virtual void display() const = 0;
    using Item::getId;
    using Item::setId;
};



class Admin : public User {

public:
    Admin() {
        account = "admin";
        password = "password";
        id = 0;
    }
};
class Customer : public User {
private:
    int num_ContainedPackage;
    int num_OutgoingPackage;
    string tel;
    int starLevel;
public:
    int getNumContainedPackage() const { return num_ContainedPackage; }
    int getNumOutgoingPackage() const { return num_OutgoingPackage; }
    string getTel() const { return tel; }
    int getStarLevel() const { return starLevel; }
    void PickupPackage(int id) ;
    void SendPackage(int id) ;
};

class Worker : public User {
private:
    
public:
    string serialize() override ;
    void deserialize(string line) override ;

    Worker() = default;
    Worker(const string& acc, const string& pwd) : User(acc, pwd) {};
    ~Worker() = default;

    void display() const override ;

    using Item::getId;
    using Item::setId;

    void RecievePackage(int id) ;
    void SendPackage(int id) ;
    void ContianPackage(int id) ;

    friend class WorkerManager;
};