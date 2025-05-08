#include<bits/stdc++.h>
#include "walker.h"
#include "thief.h"
#include "police.h"
using namespace std;

int main() {
    PoliceStation station;
    Police p1, p2, p3;
    station.addOfficer(p1);
    station.addOfficer(p2);
    station.addOfficer(p3);
    Thief t1(100), t2(200), t3(300), t4(400);
    p1.arrest(t2);
    p1.arrest(t3);
    p2.arrest(t4);
    station.setReputation(100);
    cout << "Total reputation: " << station.getTotalReputation() << endl;
    station.getEveryBonus();
    return 0;
}