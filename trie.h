#include <bits/stdc++.h>
using namespace std;

class Trie_Node {
    bool is_word;
    unordered_map<char, Trie_Node*> children;
    vector<string> definition;
    public:
        Trie_Node(string d = "") {
            is_word = 0;
            if (d != "") {
                definition.push_back(d);
                is_word = 1;
            }
        }
        vector<string> get_definition() {
            return definition;
        }
        void pre_order() {
            if (children[' '] != NULL) {
                cout << ' ' << ' ';
                children[' ']->pre_order();
            }
            if (children['\''] != NULL) {
                cout << '\'' << ' ';
                children['\'']->pre_order();
            }
            if (children['-'] != NULL) {
                cout << '-' << ' ';
                children['-']->pre_order();
            }
            for (int i = 'a'; i <= 'z'; ++i) {
                if (children[(char)i] != NULL) {
                    cout << (char)i << ' ';
                    children[(char)i]->pre_order();
                }
            }
        }
        void wordlist(vector<string> *&words, string *&word) {
            if (is_word) words->push_back(*word);
            if (children[' '] != NULL) {
                *word += ' ';
                children[' ']->wordlist(words, word);
                *word = word->substr(0, word->length()-1);
            }
            if (children['\''] != NULL) {
                *word += '\'';
                children['\'']->wordlist(words, word);
                *word = word->substr(0, word->length()-1);
            }
            if (children['-'] != NULL) {
                *word += '-';
                children['-']->wordlist(words, word);
                *word = word->substr(0, word->length()-1);
            }
            for (int i = 'a'; i <= 'z'; ++i) {
                if (children[(char)i] != NULL) {
                    *word += (char)i;
                    children[(char)i]->wordlist(words, word);
                    *word = word->substr(0, word->length()-1);
                }
            }
        }
        Trie_Node *insert(char key, string def = "") {
            Trie_Node *child = children[key];
            if (child == NULL) {
                child = new Trie_Node(def);
                children[key] = child;
            } else if (def != "") {
                children[key]->definition.push_back(def);
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
        vector<string> definition(string key) {
            Trie_Node *current = root;
            for (int i = 0; i < key.length(); ++i) {
                current = current->child(key[i]);
                if (current == NULL) return {};
            }
            return current->get_definition();
        }
        void pre_order() {
            root->pre_order();
            cout << endl;
        }
        vector<string> wordlist() {
            vector<string> *words = new vector<string>();
            string *word = new string("");
            root->wordlist(words, word);
            // cout << words->size() << endl;
            return *words;
        }
        vector<string> spell_check(string word_to_correct) {
            vector<string> closest_words;
            int closest_distance = 10000;
            int dist[50][50];
            int length1 = word_to_correct.length();
            int length2;

            auto start = chrono::system_clock::now();
            vector<string> words = wordlist();
            auto end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            cout << "Trie wordlist took:       " << elapsed_seconds.count() << "s";

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
//     Trie *trying = new Trie();
//     trying->insert("hello", "it's a very useful word");
//     trying->insert("what", "yeah");
//     trying->insert("alpha", "yeah");
//     trying->insert("alphr", "yeah");
//     trying->insert("beta", "yeah");
//     trying->insert("charlie", "yeah");
//     trying->insert("delta", "yeah");
//     trying->insert("echo", "yeah");
//     trying->insert("ferguso", "yeah");
//     trying->pre_order();
//     // cout << trying->definition("helr") << endl;
//     vector<string> wordlist = trying->wordlist();
//     for (auto i : wordlist) {
//         cout << i << ' ';
//     }
//     cout << endl;
//     for (auto i : trying->spell_check("apple"))
//         cout << i << endl;
// }