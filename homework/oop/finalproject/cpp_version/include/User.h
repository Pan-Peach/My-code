#pragma once
#include <string>

using namespace std;

class User {
protected:
    string account;
    string password;
    int id=0;
public:
    virtual void serialize(FILE* file) = 0;
    virtual void deserialize(FILE* file) = 0;

    User() = default;
    User(const string& acc, const string& pwd) : account(acc), password(pwd) {}
    virtual ~User() = default;
    virtual void display() = 0;
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
    void serialize(FILE* file) override ;
    void deserialize(FILE* file) override ;

    Worker() = default;
    Worker(const string& acc, const string& pwd) : User(acc, pwd) {};
    ~Worker() = default;

    void display() override ;

    void RecievePackage(int id) ;
    void SendPackage(int id) ;
    void ContianPackage(int id) ;

    friend class WorkerManager;
};