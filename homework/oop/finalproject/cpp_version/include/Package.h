#pragma once
#include <string>
#include <ctime>

using namespace std;

class Container; // 前向声明

class Package {
protected:
    float weight;
    float volume;
    string code;
    int id;
    string company;
    int outAddress;
    int inAddress;
    time_t timestamp;

public:
    Package(float w, float v);
    Package(float w, float v, const string& c, const int& id, const string& company, int outAddr, int inAddr);
    virtual ~Package() = default;
    
    string getCode() const { return code; }
    
    void setCode(const string& c) { code = c; }
    
    virtual double calculateCost() = 0;
    virtual void display() const = 0;

    friend class PackageManager; 
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

class ContainedPackage : public Package {
private:
    string ContainerName;
    Container* container;
};

class PendingPackage : public Package {
 
};