#include<bits/stdc++.h>

using namespace std;

int main(){
    char in;
    stack<int> s;
    string num;
    while(cin>>in){
        if(in>='0'&&in<='9'){
            num+=in;
        }
        else if(in=='.'){
            s.push(stoi(num));
            num.clear();
        }
        else if(in=='@') break;
        else if(in=='+'){
            int a=s.top(); s.pop();
            int b=s.top(); s.pop();
            s.push(a+b);
        }
        else if(in=='-'){
            int a=s.top(); s.pop();
            int b=s.top(); s.pop();
            s.push(b-a);
        }
        else if(in=='*'){
            int a=s.top(); s.pop();
            int b=s.top(); s.pop();
            s.push(a*b);
        }
        else if(in=='/'){
            int a=s.top(); s.pop();
            int b=s.top(); s.pop();
            s.push(b/a);
        }
    }
    cout<<s.top()<<endl;
    return 0;
}

