#include<bits/stdc++.h>
using namespace std;

struct Node {
            int data;
            Node* left;
            Node* right;
            Node* fa;
            Node(int val) : data(val), left(nullptr), right(nullptr) {}
        };

class BinaryTree {
    public:
        
    void iterativeInorder(Node* node, vector<int>& result) {
        if (!node) return;
        stack<Node*> st;
        Node* curr = node;
        
        while (curr || !st.empty()) {
            while (curr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top();
            st.pop();
            result.push_back(curr->data);
            curr = curr->right;
        }
    }

        void inorder(Node* node) {
            if (!node) return;
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }

        void preorder(Node* node) {
            if (!node) return;
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }

        void postorder(Node* node) {
            if (!node) return;
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }

        Node* findNode(int val) {
        if (!root) return nullptr;
        
        stack<Node*> st;
        st.push(root);
        
        while (!st.empty()) {
            Node* curr = st.top();
            st.pop();
            
            if (curr->data == val) {
                return curr;
            }
            
            if (curr->right) st.push(curr->right);
            if (curr->left) st.push(curr->left);
        }
        return nullptr;
    }
        public:
        Node* root;
        BinaryTree() : root(nullptr) {}
    
        void buildByPreorderSimple(queue<int>& preorder) {
        if (preorder.empty()) return;
        
        stack<pair<Node*, int>> st; 
        int val = preorder.front();
        preorder.pop();
        
        if (val == 0) return;
        
        root = new Node(val);
        st.push({root, 0});
        
        while (!preorder.empty()) {
            val = preorder.front();
            preorder.pop();
            
            auto& [curr, state] = st.top();
            
            if (val == 0) {
                if (state == 0) {
                    state = 1; 
                } else {
                    st.pop(); 
                }
            } else {
                Node* newNode = new Node(val);
                newNode->fa = curr;
                
                if (state == 0) {
                    curr->left = newNode;
                    state = 1; 
                    st.push({newNode, 0});
                } else {
                    curr->right = newNode;
                    st.pop(); 
                    st.push({newNode, 0});
                }
            }
        }
    }

        void buildByPreorder(Node*& node, queue<int>& preorder, Node* fa) {
            if(preorder.empty()) return;
            int val = preorder.front();
            preorder.pop();
            if(val == 0) {
                node = nullptr;
                return;
            }else{
                node = new Node(val);
                node->fa = fa;
                buildByPreorder(node->left, preorder, node);
                buildByPreorder(node->right, preorder, node);
            }
            
        }

        void outputorders(){
            preorder(root);
            cout << endl;
            inorder(root);
            cout << endl;
            postorder(root);
            cout << endl;
        }

        // bool query(Node* node, int k){
        //     if(!node) return false;
        //     if(node->data == k){
        //         if(node->fa == 0) cout << 0 << endl;
        //         else cout << node->fa << endl;
        //         return true;
        //     }
        //     bool left = query(node->left, k);
        //     if(left) return true;
        //     bool right = query(node->right, k);
        //     return right;
        // }

        Node* getNode(Node* node, int val){
            if(!node) return nullptr;
            if(node->data == val) return node;
            Node* left = getNode(node->left, val);
            if(left) return left;
            Node* right = getNode(node->right, val);
            return right;
        }

        void deleteSubtree(Node* &node){
            if(!node) return;

            
            deleteSubtree(node->left);
            deleteSubtree(node->right);

            delete node;
            
            node = nullptr;
        }
};


int main() {
    string s;
    queue<int> preorder;
    getline(cin, s);
    for(size_t i = 0; i < s.size(); ) {
        while (i < s.size() && s[i] == ' ') i++;
        if (i >= s.size()) break;
        int num = 0;
        while (i < s.size() && isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
            i++;
        }
        preorder.push(num);
    }

    BinaryTree tree;
    tree.buildByPreorderSimple(preorder);
    int m,k;
    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> k;
        Node* target = tree.findNode(k);
        Node* pa = target ? target->fa : nullptr;
        if(pa){
            if(pa->left == target) pa->left = nullptr;
            else if(pa->right == target) pa->right = nullptr;
        }
        if(!target) {
            cout << 0 << endl;
            continue;
        }
        else{
            tree.deleteSubtree(target);
        }
        vector<int> inorderResult;
        tree.iterativeInorder(tree.root,inorderResult );
        for(size_t j = 0; j < inorderResult.size(); j++){
            
            cout << inorderResult[j]<<" ";
        }
        cout << endl;

    }
    return 0;
}