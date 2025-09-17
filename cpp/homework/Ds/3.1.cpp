 #include<bits/stdc++.h>
using namespace std;

struct List{
    int data;
    List* next;
};


void remove(int n, List* head){
    List* p=head;
    List* q=head->next;
    while(q!=NULL){
        if(q->data==n){
            p->next=q->next;
            delete q;
            return;
        }
        p=p->next;
        q=q->next;
    }
}

void reverse(List* head){
    List* p=head->next;
    List* q=NULL;
    List* r=NULL;
    while(p!=NULL){
        r=q;
        q=p;
        p=p->next;
        q->next=r;
    }
    head->next=q;
}

void removeRange(int mink, int maxk, List* head){
    List* p=head;
    List* q=head->next;
    while(q!=NULL){
        if(q->data>mink&&q->data<maxk){
            p->next=q->next;
            delete q;
            q=p->next;
        }
        else{
            p=p->next;
            q=q->next;
        }
    }
}

void insertBefore(int s, int t, List* head){
    List* pre=head;
    List* cur=head->next;
    while(cur!=nullptr){
        if(cur->data==s){
            List* node = new List;
            node->data=t;
            node->next=cur;
            pre->next=node;
        }
        pre=cur;
        cur=cur->next;
    }
}

void stackRemove(int m, stack<int>& s){
    stack<int> temp;
    while(!s.empty()){
        int top=s.top();
        s.pop();
        if(top!=m){
            temp.push(top);
        }
    }
    while(!temp.empty()){
        s.push(temp.top());
        temp.pop();
    }
}