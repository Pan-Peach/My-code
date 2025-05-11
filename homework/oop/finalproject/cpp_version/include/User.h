#pragma once
#include <string>

using namespace std;

class User {
protected:
    string name;
    string account;
    string password; 
    string tel;
    int id;
    int sentCount;
    int receivedCount;
    int starLevel;

public:
    User(const string& name, const string& account, const string& password);
    virtual ~User() = default;

    // Getters
    string getName() const { return name; }
    string getAccount() const { return account; }
    string getTel() const { return tel; }
    int getId() const { return id; }
    int getStarLevel() const { return starLevel; }

    virtual bool authenticate(const string& inputPassword) const;
    virtual void updateStarLevel();
    
    friend class UserManager;
};
