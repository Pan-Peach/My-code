#pragma once
#include <string>
#include <ctime>
#include "Item.h"

using namespace std;

class Container; // 前向声明

class Package:public Item {
protected:
    float weight;
    float volume;
    string code;
    string company;
    int outAddress;
    int inAddress;
    time_t timestamp;

public:
    Package() = default;
    Package(float w, float v, const string& c, const string& co, int outAddr, int inAddr, time_t ts = time(0))
        : weight(w), volume(v), code(c), company(co), outAddress(outAddr), inAddress(inAddr), timestamp(ts) {};
    virtual ~Package() = default;
    virtual string serialize() = 0;
    virtual void deserialize(string line) = 0;
    virtual void display() const = 0;
    friend class PackageManager; 
};

// 派生类
class IncomingPackage : public Package {
private:
    string receiverTel;
    string receiverName;

public:
    IncomingPackage() = default;
    IncomingPackage(float w, float v, const string& rName, const string& rTel);
    string serialize() override;
    void deserialize(string line) override;
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
    OutgoingPackage() = default;
    OutgoingPackage(float w, float v, const string& sName, const string& rName);
    double calculateCost();
    string serialize() override;
    void deserialize(string line) override;
    void display() const override;
};

class ContainedPackage : public Package {
private:
    string ContainerName;
    Container* container;
    int OwnerId;
public:
    ContainedPackage() = default;
    ContainedPackage(float w, float v, const string& cName, Container* c);
    ~ContainedPackage() = default;

    string serialize() override;
    void deserialize(string line) override;
    void display() const override;

    int getOwnerId() const { return OwnerId; }
};

class PendingPackage : public Package {
public:
    string serialize() override;
    void deserialize(string line) override;
    void display() const override;
};