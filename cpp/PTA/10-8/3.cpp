#include<iostream>
using namespace std;

class Queue{
    private:
        struct Node{
            int data;
            Node* next;
            Node(int d, Node* n = nullptr):data(d), next(n){}
        };
        Node* head;
        Node* tail;
        int size;
    public:
        Queue(){
            head = new Node(0);
            tail = head;
            size = 0;
        }

        ~Queue(){
            Node* cur = head;
            while(cur){
                Node* next = cur->next;
                delete cur;
                cur = next;
            }
        }
        int getSize() const{
            return size;
        }
        void push(int d){
            Node* newNode = new Node(d);
            tail->next = newNode;
            tail = newNode;
            size++;
        }
        
        void pop(){
            if(size == 0) {
                cout<<"invalid"<<endl;
                return;
            }
            Node* first = head->next;
            cout<<first->data<<endl;
            head->next = first->next;
            delete first;
            size--;
            if(size == 0) tail = head; 
        }
};

int main(){
    Queue q;
    int n;
    cin>>n;
    for(int i = 0; i < n; i++){
        int op;
        cin>>op;
        if(op == 1){
            int d;
            cin>>d;
            q.push(d);
        }else if(op == 0){
            q.pop();
        }
    }
    return 0;
}

