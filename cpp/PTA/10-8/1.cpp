#include<iostream>
using namespace std;



class List{
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
        List(){
            head = new Node(0);
            tail = head;
            size = 0;
        }

        ~List(){
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
        void push_back(int d){
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

        void push_after(int pos, int d){
            if(pos < 0 || pos > size) return;
            Node* cur = head;
            for(int i = 0; i < pos; i++){
                cur = cur->next;
            }
            Node* newNode = new Node(d, cur->next);
            cur->next = newNode;
            if(cur == tail) tail = newNode;
            size++;
        }

        void delete_pos(int pos){
            if(pos <= 0 || pos > size) return;
            Node* cur = head;
            for(int i = 1; i < pos; i++){
                cur = cur->next;
            }
            Node* toDelete = cur->next;
            if(!toDelete) return;
            cur->next = toDelete->next;
            if(toDelete == tail) tail = cur;
            delete toDelete;
            size--;
        }

        void print() const{
            Node* cur = head->next;
            while(cur){
                cout << cur->data << " ";
                cur = cur->next;
            }
            cout << endl;
        }
};

int main(){
    List lst=List();
    int n,m;
    cin >> n;
    for(int i = 0; i < n; i++){
        int d;
        cin >> d;
        lst.push_back(d);
    }
    cin >> m;
    for(int i = 0; i < m; i++){
        int op;
        cin >> op;
        if(op == 0){
            int pos, d;
            cin >> pos >> d;
            lst.push_after(pos, d);
        }else if(op == 1){
            int pos;
            cin >> pos;
            lst.delete_pos(pos);
        }
    }

    lst.print();
    return 0;

}