#include<bits/stdc++.h>
using namespace std;
//const int MN=1000;
int gid=0;

class Node{
public:
    char val;
    int fre;
    Node* l;
    Node* r;
    int birth;
    Node(): val('#'),fre(0),birth(0){}
    Node(char val, int fre, int birth): val(val), fre(fre), birth(birth), l(nullptr), r(nullptr){}
    Node(int freq, Node* left, Node* right, int birth_)
    : val('#'), fre(freq), l(left), r(right), birth(birth_) {}

    // bool operator<(const Node& rhs) const {
    //     if (fre != rhs.fre) return fre > rhs.fre;   
    //     if (val == '#' && rhs.val != '#') return false; 
    //     if (val != '#' && rhs.val == '#') return true;
    //     return birth > rhs.birth;                   
    // }
    
};

struct Cmp {
    bool operator()(Node* a, Node* b) const {
        if (a->fre != b->fre) return a->fre > b->fre;  
        bool aIsLeaf = (a->val != '#');
        bool bIsLeaf = (b->val != '#');
        
        if (a->val != '#' && b->val == '#') return false; 
        if (a->val == '#' && b->val != '#') return true;
        return a->birth > b->birth;                     
    }
};

Node* merge(priority_queue<Node*,vector<Node*>, Cmp>& pq){
    
    while(pq.size()>1){
        Node* l=pq.top(); pq.pop();
        Node* r=pq.top(); pq.pop();
        int newFreq=l->fre+r->fre;
        pq.push(new Node(newFreq,l,r,++gid));

    }
    return pq.top();
}

void dfs(map<char,string>& mp, Node* p, string path){
    if(!p) return;
    if (p->val != '#') {                // 叶子
        mp[p->val] = path.empty() ? "0" : path; // 若只有根也算一位
        return;
    }
    dfs(mp, p->l, path + '0');
    dfs(mp, p->r, path + '1');
}

void preorder(Node* node){
        if(node==nullptr){
            cout<<'0'<<' ';
            return;
        }
        char cur=node->val;
        cout<<cur<<' ';
        preorder(node->l);
        preorder(node->r);
        return;
}

int cptLength(map<char,string>& mp,string raw){
    int len=0;
    for(auto c:raw){
        len+=mp[c].size();
    }
    if(len%8==0) return len/8;
    else return len/8+1;
}

void decode(Node* huff, string code){

    if(code.empty()) {
        cout << "INVALID" << endl;
        return;
    }
    
    if(huff->val != '#') {
        for(char c : code) {
            if(c != '0') { 
                cout << "INVALID" << endl;
                return;
            }
        }
        // 输出对应次数的字符
        for(int i = 0; i < code.size(); i++) {
            cout << huff->val;
        }
        cout << endl;
        return;
    }
    Node* cur=huff;
    string out;
    int len=code.size();
    for(int i=0;i<code.size();i++){
        if(!cur){
            cout<<"INVALID"<<endl;
            return;
        }
        
        char c=code[i];
        if(cur->val=='#'){
        if(c=='0'){
            cur=cur->l;
        }
        if(c=='1') cur=cur->r;
        }
        if(cur->val!='#'){
            out+=cur->val;
            cur=huff;
            continue;
        }
    }
    if(cur!=huff) {
        cout<<"INVALID"<<endl;
        return;
    }
    
    cout<<out;
    cout<<endl;
    return;
}

class TextChar {
public:
    char val;
    int fre;
    int firstOccur;

    TextChar(char v, int f, int o) : val(v), fre(f), firstOccur(o) {}

    bool operator < (const TextChar& other) const {
        if (fre != other.fre) 
            return fre > other.fre;
        return firstOccur > other.firstOccur;
    }
};

int main(){
    string raw,huff1,huff2;
    map<char,bool> apper;
    vector<int> fre(26,0);
    vector<int> order(26,-1);
    vector<int> occurSeq(26,0);
    map<char,string> huff;
    int seqTop=0;
    cin>>raw>>huff1>>huff2;
    for(int i=0;i<raw.size();i++){
        char cur=raw[i];
        fre[cur-'a']++;
        if(order[cur-'a']==-1){
            order[cur-'a']=i;
            occurSeq[seqTop++]=cur-'a';
        }
    }
    priority_queue<Node*,vector<Node*>, Cmp> pq;

    for(int i=0;i<seqTop;i++){
        char c =  occurSeq[i]+'a';
        int idx = occurSeq[i];
        Node* cur=new Node(c,fre[idx],order[idx]);
        pq.push(cur);        
    }
    gid=order.size();
    Node* root = merge(pq);
    //preorder(root);
    cout<<raw.size()<<' ';
    dfs(huff,root,"");
    cout<<cptLength(huff,raw)<<endl;
    priority_queue<TextChar> tc;

    for(int i=0;i<seqTop;i++){
        int c=occurSeq[i];
        tc.push(TextChar(c+'a',fre[c],i));
        
    }

    while(!tc.empty()){
        char ch=tc.top().val;
        tc.pop();
        int c = ch-'a';
        cout<<(char)(c+'a')<<':'<<huff[c+'a']<<'\n';
    }
    decode(root,huff1);
    decode(root,huff2);
    return 0;
}