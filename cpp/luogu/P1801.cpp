#include<bits/stdc++.h>
using namespace std;

template<typename Compare = less<int>>
class Heap{
    private:
        vector<int> arr;
        int size=0;
        Compare cmp;

        void up(int idx){
            while(idx/2>0 && cmp(arr[idx], arr[idx/2])){ 
                swap(arr[idx], arr[idx/2]);           
                idx /= 2;                              
            }
        }
        void down(int idx){
            while(idx*2<=size){ 
                int child = idx*2; 
                if(child+1<=size && cmp(arr[child+1], arr[child])){ // 有右孩子且右孩子更小
                    child = child+1;
                }
                if(cmp(arr[child], arr[idx])){ 
                    swap(arr[child], arr[idx]);
                    idx = child; 
                }
                else break; 
            }
        }
    public:
        
        Heap(const Compare& cmp=Compare()): arr(1),cmp(cmp){} // 下标0不存元素
        void push(int val){
            arr.push_back(val);  
            size++;
            up(size);           
        }
        void pop(){
            if(size==0) return;
            arr[1] = arr[size]; 
            arr.pop_back();     
            size--;
            down(1);           
        }
        int get(){
            if(size==0) return -1; // 堆空
            return arr[1];
        }

        int size_(){
            return size;
        }

        void reset(){
            arr.clear();
            arr.push_back(0);
            size=0;
        }

        int top(){
            return arr[1];
        }
};

int main(){
    int n,m;
    cin>>n>>m;
    vector<int> a(n+1);
    vector<int> b(m+1);
    Heap<less<int>> heap;
    Heap<greater<int>> maxheap;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        //maxheap.push(a[i]);
    }
    for(int i=1;i<=m;i++) cin>>b[i];
    int cnt=0,i=1;
    
    for(int x=1;x<=m;x++){
        while(cnt!=b[x]){
            heap.push(a[cnt+1]);
            cnt++;
        }
        while(heap.size_()!=0 && maxheap.size_()!=0&& maxheap.top()>heap.top()){
            int tmp=heap.top();
            heap.pop();
            heap.push(maxheap.top());
            maxheap.pop();
            maxheap.push(tmp);
        }
        while(maxheap.size_()<i){
            maxheap.push(heap.get());
            heap.pop();
        }
        cout<<maxheap.get()<<endl;
        i++;

    }
    return 0;
}