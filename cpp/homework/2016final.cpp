#include<bits/stdc++.h>
using namespace std;

struct info{
    string name;
    bool gender;
    int age;
}llist[1000];

void in(int i){
    cin>>llist[i].name>>llist[i].gender>>llist[i].age;
}

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        in(i);
    }
    cout<<llist[n/2].name<<' ';
    if(llist[n/2].gender) cout<<"Male"<<' ';
    else cout<<"Female"<<' ';
    cout<<llist[n/2].age;
    return 0;
}