#include <bits/stdc++.h>

using namespace std;

class AVL_Node {
    string key;
    int height;
    AVL_Node *left;
    AVL_Node *right;

    AVL_Node *right_rotate() {
        AVL_Node *x = left;
        AVL_Node *T2 = x->right;

        x->right = this;
        left = T2;

        height = 1 + max((left == NULL) ? -1 : left->height, (right == NULL) ? -1 : right->height);
        x->height = 1 + max((x->left == NULL) ? -1 : x->left->height, (x->right == NULL) ? -1 : x->right->height);

        return x; // x adalah root baru
    }

    AVL_Node *left_rotate() {
        AVL_Node *y = right;
        AVL_Node *T2 = y->left;

        y->left = this;
        right = T2;

        height = 1 + max((left == NULL) ? -1 : left->height, (right == NULL) ? -1 : right->height);
        y->height = 1 + max((y->left == NULL) ? -1 : y->left->height, (y->right == NULL) ? -1 : y->right->height);

        return y; // y adalah root baru
    }

    public:
    
        AVL_Node(string k, AVL_Node *l = NULL, AVL_Node *r = NULL, int h = 0) {
            key = k;
            left = l;
            right = r;
            height = h;
        }

        void pre_order() {
            cout << key << " ";
            if (left != NULL) left->pre_order();
            if (right != NULL) right->pre_order();
        }

        void in_order() {
            if (left != NULL) left->pre_order();
            cout << key << " ";
            if (right != NULL) right->pre_order();
        }

        AVL_Node *insert(string k) {
            if (k < key && left != NULL) left = left->insert(k);
            else if (k > key && right != NULL) right = right->insert(k);
            else if (k < key) left = new AVL_Node(k);
            else if (k > key) right = new AVL_Node(k);

            int left_height = (left == NULL) ? -1 : left->height;
            int right_height = (right == NULL) ? -1 : right->height;

            height = 1 + max(left_height, right_height);
            int bal = left_height - right_height;

            if (left != NULL && bal > 1 && k < left->key) return right_rotate();
            if (left != NULL && bal > 1 && k > left->key) {
                left = left->left_rotate();
                return right_rotate();
            }
            if (right != NULL && bal < -1 && k > right->key) return left_rotate();
            if (right != NULL && bal < -1 && k < right->key) {
                right = right->right_rotate();
                return left_rotate();
            }
            return this;
        }
};

class AVL_Tree {
    AVL_Node *root;
    public:
        AVL_Tree() {
            root = NULL;
        }
        AVL_Tree(string key) {
            root = new AVL_Node(key);
        }
        void insert(string key) {
            if (root == NULL) root = new AVL_Node(key);
            else root = root->insert(key); 
        }
        void pre_order() {
            if (root != NULL) root->pre_order();
            cout << endl;
        }
        void in_order() {
            if (root != NULL) root->in_order();
            cout << endl;
        }
};