#include<iostream>
using namespace std;

class Stack{
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
        Stack(){
            head = new Node(0);
            tail = head;
            size = 0;
        }

        ~Stack(){
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
            if(size == 0){
                head->next = newNode;
                tail = newNode;
            }else{
                tail->next = newNode;
                tail = newNode;

            }
            size++;
        }
        
        void pop(){
            if(size == 0) {
                cout<<"invalid"<<endl;
                return;
            }
            Node* cur = head;
            for(int i = 1; i < size; i++){
                cur = cur->next;
            }
            cout<<tail->data<<endl;
            delete tail;
            tail = cur;
            tail->next = nullptr;
            size--;
        }

        int top() const{
            if(size == 0) throw runtime_error("Stack is empty");
            return tail->data;
        }
};

int main(){
    Stack s;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int op;
        cin>>op;
        if(op==0){
            s.pop();
        }
        else if(op==1){
            int d;
            cin>>d;
            s.push(d);
        }
       
    }
    return 0;
}