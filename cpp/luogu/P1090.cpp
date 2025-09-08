#include<bits/stdc++.h>
using namespace std;

class MinHeap{
    private:
        vector<int> arr;
        int size;

        void up(int index){
            while(index > 0){
                int pa=(index-1)/2;
                if(arr[pa] > arr[index]){
                    swap(arr[pa], arr[index]);
                    index = pa;
                } else {
                    break;
                }

            }
        }

        void down(int index){
            while(index<size){
                int left=2*index+1;
                int right=2*index+2;
                int smallest=index;
                if(left<size && arr[left]<arr[smallest]){
                    smallest=left;
                }
                if(right<size && arr[right]<arr[smallest]){
                    smallest=right;
                }
                if(smallest!=index){
                    swap(arr[smallest], arr[index]);
                    index=smallest;
                } else {
                    break;
                }
            }
        }
    public:

        MinHeap(): arr(), size(0) {}
        void push(int val){
            arr.push_back(val);
            size++;
            up(size-1);
        }
        void pop(){
            if(size==0) return;
            arr[0]=arr[size-1];
            arr.pop_back();
            size--;
            down(0);
        }
        int top(){
            if(size==0) return -1;
            return arr[0];
        }
        int getSize(){
            return size;
        }
};

int main(){
    MinHeap heap;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        heap.push(x);
    }
    int ans=0,a,b;
    while(heap.getSize()>1){
        a=heap.top();
        heap.pop();
        b=heap.top();
        heap.pop();
        heap.push(a+b);
        ans+=a+b;
    }
    cout<<ans;
    return 0;
}