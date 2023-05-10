#include <bits/stdc++.h>
using namespace std;

class AVL_Node {
    string key;
    int height;
    vector<string> definition;
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
            definition.push_back(d);
        }
        string get_key() {
            return key;
        }
        vector<string> get_definition() {
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
            if (left != NULL) left->in_order();
            cout << key << " ";
            if (right != NULL) right->in_order();
        }
        void wordlist(vector<string> *&words) {
            if (left != NULL) left->wordlist(words);
            words->push_back(key);
            if (right != NULL) right->wordlist(words);
        }
        AVL_Node *insert(string k, string def) {
            if (k < key && left != NULL) left = left->insert(k, def);
            else if (k > key && right != NULL) right = right->insert(k, def);
            else if (k < key) left = new AVL_Node(k, def);
            else if (k > key) right = new AVL_Node(k, def);
            else if (k == key) definition.push_back(def);

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
        vector<string> definition(string key) {
            AVL_Node *current = root;
            string current_key = current->get_key();
            while (current_key != key) {
                if (key < current_key) {
                    current = current->get_left();
                } else {
                    current = current->get_right();
                }
                if (current == NULL) return {};
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
        vector<string> wordlist() {
            vector<string> *words = new vector<string>();
            if (root != NULL) root->wordlist(words);
            return *words;
        }
        vector<string> spell_check(string word_to_correct) {
            vector<string> closest_words;
            int closest_distance = 10000;
            int dist[50][50];
            int length1 = word_to_correct.length();
            int length2;
            vector<string> words = wordlist();
            for (int i = 0; i < 50; ++i) {
                dist[0][i] = i;
                dist[i][0] = i;
            }
            for (int i = 0; i < words.size(); ++i) {
                string word_to_compare = words[i];
                length2 = word_to_compare.length();
                for (int m = 1; m <= length1; ++m) {
                    for (int n = 1; n <= length2; ++n) {
                        if (word_to_correct[m-1] == word_to_compare[n-1]) {
                            dist[m][n] = min(dist[m-1][n-1], min(dist[m-1][n]+1, dist[m][n-1]+1));
                        } else {
                            dist[m][n] = min(dist[m-1][n-1], min(dist[m-1][n], dist[m][n-1])) + 1;
                        }
                    }
                }
                // cout << word_to_compare << endl;
                // for (int m = 0; m < length1; ++m) {
                //     for (int n = 0; n < length2; ++n) {
                //         cout << dist[m][n] << ' ';
                //     }
                //     cout << endl;
                // }
                if (dist[length1][length2] < closest_distance) {
                    closest_distance = dist[length1][length2];
                    closest_words.clear();
                    closest_words.push_back(word_to_compare);
                } else if (dist[length1][length2] == closest_distance) {
                    closest_words.push_back(word_to_compare);
                }
            }
            return closest_words;
        }
};

// int main() {
//     AVL_Tree *avl = new AVL_Tree("hello", "yabolh");
//     avl->insert("what", "yeah");
//     avl->insert("alpha", "yeah");
//     avl->insert("beta", "yeah");
//     avl->insert("charlie", "yeah");
//     avl->insert("delta", "yeah");
//     avl->insert("echo", "yeah");
//     avl->insert("ferguso", "yeah");
//     // cout << avl->definition("hello") << endl;
//     // cout << avl->definition("what") << endl;
//     avl->in_order();
//     for (auto i : avl->spell_check("apple"))
//         cout << i << endl;
// }