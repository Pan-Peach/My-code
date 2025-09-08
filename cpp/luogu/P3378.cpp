#include<bits/stdc++.h>
using namespace std;

class Heap{
    private:
        vector<int> a;
        int size;
        void up(int i){
            while(i>1 && a[i]<a[i/2]){
                swap(a[i], a[i/2]);
                i /= 2;
            }
            return;
        }
        void down(int i){
            while(i*2<=size){
                int t = i*2;
                if(t+1<=size && a[t+1]<a[t]) t++;
                if(a[t]<a[i]){
                    swap(a[t], a[i]);
                    i = t;
                }
                else break;
            }
            return;
        }
    public:
        Heap():size(0){
            a.push_back(0);
        }
        void push(int x){
            a.push_back(x);
            size++;
            up(size);
            return;
        }
        void pop(){
            if(size==0) return;
            a[1] = a[size];
            a.pop_back();
            size--;
            down(1);
            return;
        }
        int top(){
            if(size==0) return -1;
            return a[1];
        }
        bool empty(){
            return size==0;
        }
};

int main(){
    Heap h;
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int op,x;
        cin >> op;
        if(op==1){
            cin >> x;
            h.push(x);
        }
        else if(op==2){
            cout<<h.top();
            if(i!=n-1) cout<<endl;
        }
        else if(op==3){
            h.pop();
        }
    }
    return 0;
}