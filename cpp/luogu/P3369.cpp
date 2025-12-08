#include<bits/stdc++.h>
using namespace std;

class AVLTree {
    private:

    class Node {
        public:
        int val, cnt, height, size;
        Node *left, *right;
        Node(int v) : val(v), cnt(1), height(1), size(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getSize(Node* node) {
        return node ? node->size : 0;
    }

    void update(Node* node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
            node->size = node->cnt + getSize(node->left) + getSize(node->right);
        }
    }

    void rotateLeft(Node*& node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        update(node);
        update(newRoot);
        node = newRoot;
    }

    void rotateRight(Node*& node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        update(node);
        update(newRoot);
        node = newRoot;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* balance(Node* node){

    }

    Node* insert(Node* node, int val){
        Node* newNode = new Node(val);
        if (!node) return newNode;
        if (val == node->val) {
            node->cnt++;
            newNode = node;
    }

    public:
    
    AVLTree() : root(nullptr) {}

    void insert(int val) {
        
    }
};