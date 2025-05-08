#ifndef Police_H
#define Police_H

#include <iostream>
#include "thief.h"
using namespace std;

class Police{
public:
    Police(){bonus = 0; reputation = 0;};
    Police(int b, int r):bonus(b), reputation(r){};
    virtual ~Police()=default;
    int getBonus() const {
        return bonus;
    }
    void setBonus(int b) {
        bonus = b;
    }
    int getReputation() const {
        return reputation;
    }
    void setReputation(int r) {
        reputation = r;
    }
    void arrest(Thief& t) {
        cout << "Police is arresting the thief!" << endl;
        int stolenMoney = t.getMoney();
        t.setMoney(0); // Use the setter method to modify money
        bonus += stolenMoney; // Add stolen money to police bonus
        reputation += 1; // Increase reputation for successful arrest
    }
private:
    int bonus;
    int reputation;
};

class PoliceStation{
public:
    PoliceStation(){};
    ~PoliceStation()=default;
    vector<Police*> officers;
    void addOfficer(Police& officer) {
        officers.push_back(&officer);
    }
    int getTotalReputation() const {
        int totalReputation = reputation;
        for (const auto officer : officers) {
            totalReputation += officer->getReputation();
        }
        return totalReputation;
    }
    void getEveryBonus() const{
        for(const auto officer: officers){
            cout << "Bonus of officer: " << officer->getBonus() << endl;
        }

    }

    void setReputation(int r) {
        reputation = r;
    }
private:
    int reputation;
};

#endif

