#include<bits/stdc++.h>
using namespace std;

const int WORN=-1111111;

int fastPow(int base,int exp){
    if(exp==0) return 1;
    if(exp==1) return base;
    if(exp%2==0){
        int half = fastPow(base,exp/2);
        return half*half;
    }
    else{
        return base*fastPow(base,exp-1);
    }
}

int getPrecedence(char op){
    if(op=='+' || op=='-') return 1;
    if(op=='*' || op=='/') return 2;
    if(op=='^') return 3;
    return 0;
}

int calculate(int a,int b,char op){
    switch(op){
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': {
            if(b==0) return WORN;
            return a/b;
        }
        case '^': return fastPow(a,b);
    }
    return WORN;
}

string makeBack(string &s){

}

void compute(string &s){
    int n = s.length();
    stack<char> op;
    stack<int> vals;
    string sub;
    int idx=0;
    while(s.size()>0){
        string num;
        char cur=s[idx];
        if(isdigit(cur)){
            while(idx<s.size() && isdigit(s[idx])){
                num.push_back(s[idx]);
                idx++;
            }
            vals.push(stoi(num));
            num.clear();
            s.erase(0,idx);
            idx=0;
        }
        else if(cur=='('){
            op.push(cur);
            s.erase(0,1);
        }
        else if(cur==')'){
            while(!op.empty() && op.top()!='('){
                int b=vals.top(); vals.pop();
                int a=vals.top(); vals.pop();
                char oper=op.top(); op.pop();
                int res=calculate(a,b,oper);
                if(res==WORN){
                    cout<<"INVALID"<<endl;
                    return;
                }
                vals.push(res);
            }
            if(!op.empty() && op.top()=='(') op.pop();
            s.erase(0,1);
        }
        else if(getPrecedence(cur)>0){
            while(!op.empty() && getPrecedence(op.top())>=getPrecedence(cur)){
                int b=vals.top(); vals.pop();
                int a=vals.top(); vals.pop();
                char oper=op.top(); op.pop();
                int res=calculate(a,b,oper);
                if(res==WORN){
                    cout<<"INVALID"<<endl;
                    return;
                }
                vals.push(res);
            }
            op.push(cur);
            s.erase(0,1);
        }
    }
    if(!op.empty()){
        while(!op.empty()){
            int b=vals.top(); vals.pop();
            int a=vals.top(); vals.pop();
            char oper=op.top(); op.pop();
            int res=calculate(a,b,oper);
            if(res==WORN){
                cout<<"INVALID"<<endl;
                return;
            }
            vals.push(res);
        }
    }
    cout<<vals.top()<<endl;
    return;
}

int main(){
    string s;
    while(getline(cin,s)){
        compute(s);
    }
    return 0;
}