#include <bits/stdc++.h>
using namespace std;

class AVL_Node {
    string key;
    int height;
    string definition;
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
        AVL_Node(string k, string d, AVL_Node *l = NULL, AVL_Node *r = NULL, int h = 0) {
            key = k;
            left = l;
            right = r;
            height = h;
            definition = d;
        }
        string get_key() {
            return key;
        }
        string get_definition() {
            return definition;
        }
        AVL_Node *get_left() {
            return left;
        }
        AVL_Node *get_right() {
            return right;
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
        AVL_Node *insert(string k, string definition) {
            if (k < key && left != NULL) left = left->insert(k, definition);
            else if (k > key && right != NULL) right = right->insert(k, definition);
            else if (k < key) left = new AVL_Node(k, definition);
            else if (k > key) right = new AVL_Node(k, definition);

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
        AVL_Tree(string key, string definition) {
            root = new AVL_Node(key, definition);
        }
        void insert(string key, string definition) {
            if (root == NULL) root = new AVL_Node(key, definition);
            else root = root->insert(key, definition); 
        }
        string definition(string key) {
            AVL_Node *current = root;
            string current_key = current->get_key();
            while (current_key != key) {
                if (key < current_key) {
                    current = current->get_left();
                } else {
                    current = current->get_right();
                }
                if (current == NULL) return "";
                current_key = current->get_key();
            }
            return current->get_definition();
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

int main() {
    AVL_Tree *avl = new AVL_Tree("hello", "yabolh");
    avl->insert("what", "yeah");
    cout << avl->definition("hello") << endl;
    cout << avl->definition("what") << endl;
}