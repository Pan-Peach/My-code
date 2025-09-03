#include<bits/stdc++.h>
using namespace std;

int priority(char op) {
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
    if(op == '@') return -1;
    return 0;
}

int main(){
    string in;
    string num;
    cin>>in;
    in+='@';
    stack<int> s;
    stack<char> temp;
    temp.push('#');
    for(int i=0;i<in.size();i++){
        if(in[i]>='0'&&in[i]<='9'){
            num+=in[i];
        }
        else{
            // if(num.size()>4){
            //     string tmp;
            //     for(int i=num.size()-5;i<num.size();i++){
            //         tmp+=num[i];
            //     }
            //     s.push(stoi(tmp));
            // }
            // else s.push(stoi(num));
            s.push(stoi(num));
            num.clear();
            while(priority(in[i])<=priority(temp.top())){
                if(temp.top()=='#') break;
                int b=s.top();s.pop();
                int a=s.top();s.pop();
                char op=temp.top();temp.pop();
                if(op=='+') s.push((a+b)%10000);
                if(op=='-') s.push(a-b);
                if(op=='*') s.push((a*b)%10000);
                if(op=='/') s.push(a/b);
            }
            temp.push(in[i]);

        }
    }
    string ans=to_string(s.top());
    if(ans.size()>4){
        string tmp;
        for(int i=ans.size()-4;i<ans.size();i++){
            tmp+=ans[i];
        }
        ans=tmp;
    }
    cout<<ans;
    return 0;
}