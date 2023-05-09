#include <bits/stdc++.h>
using namespace std;

class Trie_Node {
    bool is_word;
    unordered_map<char, Trie_Node*> children;
    string definition;
    public:
        Trie_Node(string d = "") {
            is_word = 0;
            definition = d;
            if (d != "") {
                is_word = 1;
            }
        }
        bool get_is_word() {
            return is_word;
        }
        string get_definition() {
            return definition;
        }
        void pre_order() {
            if (children[' '] != NULL) {
                children[' ']->pre_order();
            }
            if (children['\''] != NULL) {
                children['\'']->pre_order();
            }
            if (children['-'] != NULL) {
                children['-']->pre_order();
            }
            for (int i = 'a'; i <= 'z'; ++i) {
                if (children[(char)i] != NULL) {
                    children[(char)i]->pre_order();
                }
            }
        }
        Trie_Node *insert(char key, string d = "") {
            Trie_Node *child = children[key];
            if (child == NULL) {
                child = new Trie_Node(d);
                children[key] = child;
            }
            return child;
        }
        Trie_Node *child(char key) {
            return children[key];
        }
};

class Trie {
    Trie_Node *root;
    public:
        Trie() {
            root = new Trie_Node();
        }
        void insert(string key, string definition) {
            Trie_Node *current = root;
            for (int i = 0; i < key.length() - 1; ++i) {
                current = current->insert(key[i]);
            }
            current->insert(key[key.length()-1], definition);
        }
        string definition(string key) {
            Trie_Node *current = root;
            for (int i = 0; i < key.length(); ++i) {
                current = current->child(key[i]);
                if (current == NULL) return "";
            }
            return current->get_definition();
        }
        void pre_order() {
            root->pre_order();
        }
};

int main() {
    Trie *trying = new Trie();
    trying->insert("hello", "it's a very useful word");
    trying->pre_order();
    cout << trying->definition("helr") << endl;
}