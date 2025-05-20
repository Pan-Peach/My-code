#pragma once
#include <string>
#include <list>
#include <memory>
#include "Item.h"

using namespace std;

class ContainedPackage;
class ContainedPackageManager;

class User:public Item {
protected:
    string account;
    string password;
public:
    virtual string serialize() = 0;
    virtual void deserialize(string line) = 0;

    User() = default;
    User(const string& acc, const string& pwd) : account(acc), password(pwd) {}
    User(const string& acc, const string& pwd, const int& id) : account(acc), password(pwd), Item(id) {}
    virtual ~User() = default;
    virtual void display() const = 0;
    using Item::getId;
    using Item::setId;

    string getAccount() const { return account; }
    string getPassword() const { return password; }
};



class Admin : public User {

public:
    Admin() = default;
    Admin(const string& acc, const string& pwd) : User(acc, pwd) {};
    ~Admin() = default;
    virtual string serialize() override ;
    virtual void deserialize(string line) override ;
    void display() const override ;
};
class Customer : public User {
private:
    string name;
    int num_ContainedPackage;
    int num_OutgoingPackage;
    list<shared_ptr<ContainedPackage>> containedPackage;
    string tel;
    int starLevel;

    void getCPackagePtr(const ContainedPackageManager& containedPackage);



public:
    Customer() = default;
    Customer(const string& name, const string& acc, const string& pwd, const int& id, const int& num_OutgoingPackage, const int& num_ContainedPackage, const string& tel);
    ~Customer() = default;

    virtual string serialize() override ;
    virtual void deserialize(string line) override ;
    void display() const override ;

    int getNumContainedPackage() const { return num_ContainedPackage; }
    int getNumOutgoingPackage() const { return num_OutgoingPackage; }
    string getTel() const { return tel; }
    int getStarLevel() const { return starLevel; }
    void PickupPackage(int id) ;
    void SendPackage(int id) ;
    void CptStarLevel();

    friend class CustomerManager;
    friend class ContainedPackageManager;
};

class Worker : public User {
private:
    
public:
    string serialize() override ;
    void deserialize(string line) override ;

    Worker() = default;
    Worker(const string& acc, const string& pwd, const int& id) : User(acc, pwd, id) {};
    ~Worker() = default;

    void display() const override ;

    using Item::getId;
    using Item::setId;

    void RecievePackage(int id) ;
    void SendPackage(int id) ;
    void ContianPackage(int id) ;

    friend class WorkerManager;
};