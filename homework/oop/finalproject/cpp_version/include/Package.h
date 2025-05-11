#pragma once
#include <string>
#include <ctime>

using namespace std;

class Package {
protected:
    float weight;
    float volume;
    string code;
    string id;
    string company;
    int outAddress;
    int inAddress;
    int state;
    time_t timestamp;

public:
    Package(float w, float v);
    virtual ~Package() = default;
    
    string getCode() const { return code; }
    int getState() const { return state; }
    
    void setState(int s) { state = s; }
    void setCode(const string& c) { code = c; }
    
    virtual double calculateCost() = 0;
    virtual void display() const = 0;
};

// 派生类
class IncomingPackage : public Package {
private:
    string receiverTel;
    string receiverName;

public:
    IncomingPackage(float w, float v, const string& rName, const string& rTel);
    double calculateCost() override;
    void display() const override;
};

class OutgoingPackage : public Package {
private:
    string senderTel;
    string senderName;
    string receiverTel;
    string receiverName;
    bool isUrgent;

public:
    OutgoingPackage(float w, float v, const string& sName, const string& rName);
    double calculateCost() override;
    void display() const override;
};
