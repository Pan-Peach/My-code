#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    priority_queue<int, vector<int>, greater<int>> minq;
    priority_queue<int> maxq;
    vector<int> arr(n);
    for(int i=0; i<n; i++){
        int x;
        cin>>x;
        arr[i]=x;
    }
    minq.push(arr[0]);
    maxq.push(-1);
    cout<<minq.top()<<endl;
    for(int i=1; i<n; i++){
        minq.push(arr[i]);
        if(maxq.top()>minq.top()){
            int t1=maxq.top();
            int t2=minq.top();
            maxq.pop();
            minq.pop();
            maxq.push(t2);
            minq.push(t1);
        }
        if(i%2==0&&i!=0){
            // maxq.push(minq.top());
            // minq.pop();
            int ans=minq.top();
            cout<<ans<<endl;
        }
        else{
            maxq.push(minq.top());
            minq.pop();
            
        }
        
    }
    return 0;
}