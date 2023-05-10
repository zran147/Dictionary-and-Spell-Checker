#include <bits/stdc++.h>
#include "trie.h"
#include "avl.h"
using namespace std;

template <typename Tree>
Tree *read_dict(string file_name) {
    ifstream file;
    file.open(file_name, ios::in);
    string line, word, part_of_speech, definition;
    Tree *tree = new Tree();
    int i = 1;
    while (getline(file, line)) {
        // if (line == "") continue;
        for (int i = 0; i < line.length(); ++i) {
            line[i] = tolower(line[i]);
        }
        stringstream ss(line);

        getline(ss, word, ',');
        word.erase(remove(word.begin(), word.end(), '"'), word.end());
        // cout << word[0] << ' ' << i << endl;

        getline(ss, part_of_speech, ',');
        part_of_speech.erase(remove(part_of_speech.begin(), part_of_speech.end(), '"'), part_of_speech.end());

        getline(ss, definition);
        definition.erase(remove(definition.begin(), definition.end(), '"'), definition.end());

        tree->insert(word, part_of_speech + definition);
        ++i;
    }
    file.close();
    return tree;
}

enum MODE {AVL, TRIE, COMPARISON};

void menu(MODE mode) {
    string _mode;
    switch (mode) {
        case 0:
            _mode = "AVL";
            break;
        case 1:
            _mode = "Trie";
            break;
        case 2:
            _mode = "Comparison";
            break;
    }
    cout << "Welcome to Spell Checker and Dictionary" << endl
    << "Current Mode: " << _mode << endl
    << "> ";
}

int main() {
    AVL_Tree *avl = read_dict<AVL_Tree>("dictionary.csv");
    Trie *trie = read_dict<Trie>("dictionary.csv");
    MODE mode = COMPARISON;
    string input;
    menu(mode);
    getline(cin, input);
    while (input != "/exit") {
        if (input == "/mode avl") {
            mode = AVL;
        } else if (input == "/mode trie") {
            mode = TRIE;
        } else if (input == "/mode comparison" || input == "/mode comp") {
            mode = COMPARISON;
        } else {
            if (mode != TRIE) {
                cout << "------------------------------" << endl << "AVL" << endl << endl;
                vector<string> closest = avl->spell_check(input);
                if (input != closest[0]) {
                    cout << "Did you mean: ";
                    for (int i = 0; i < min((int)closest.size(), 5); ++i) {
                        cout << closest[i] << ' ';
                    }
                    cout << endl;
                } else {
                    cout << "Definition:" << endl;
                    for (auto def : avl->definition(input)) {
                        cout << def << endl;
                    }
                }
                cout << "------------------------------" << endl;
            }
            if (mode != AVL) {
                if (mode != COMPARISON) cout << "------------------------------" << endl;
                cout << "TRIE" << endl << endl;
                vector<string> closest = avl->spell_check(input);
                if (input != closest[0]) {
                    cout << "Did you mean: ";
                    for (int i = 0; i < min((int)closest.size(), 5); ++i) {
                        cout << closest[i] << ' ';
                    }
                    cout << endl;
                } else {
                    cout << "Definition:" << endl;
                    for (auto def : avl->definition(input)) {
                        cout << def << endl;
                    }
                }
                cout << "------------------------------" << endl;
            }
        }
        getline(cin, input); // buffer
        menu(mode);
        getline(cin, input);
    }
}