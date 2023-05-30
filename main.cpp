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
    // int i = 1;
    // char test = ' ';
    while (getline(file, line)) {
        // if (line == "") continue;
        for (int i = 0; i < line.length(); ++i) {
            line[i] = tolower(line[i]);
        }
        stringstream ss(line);

        getline(ss, word, ',');
        word.erase(remove(word.begin(), word.end(), '"'), word.end());
        // if (word[0] != test) {
        //     cout << word[0] << ' ' << i << endl;
        //     test = word[0];
        // }

        getline(ss, part_of_speech, ',');
        part_of_speech.erase(remove(part_of_speech.begin(), part_of_speech.end(), '"'), part_of_speech.end());

        getline(ss, definition);
        definition.erase(remove(definition.begin(), definition.end(), '"'), definition.end());

        tree->insert(word, part_of_speech + definition);
        // ++i;
    }
    file.close();
    return tree;
}

enum MODE {AVL, TRIE, COMPARISON};

void menu(MODE mode) {
    cout<<endl;
    cout<<"   __      __   ___  | |   ___    ___    _ __ ___     ___  "<<endl;
    cout<<"   \\ \\ /\\ / /  / _ \\ | |  / __|  / _ \\  | '_ ` _ \\   / _ \\ "<<endl;
    cout<<"    \\ V  V /  |  __/ | | | (__  | (_) | | | | | | | |  __/ "<<endl;
    cout<<"     \\_/\\_/    \\___| |_|  \\___|  \\___/  |_| |_| |_|  \\___| "<<endl;
    cout<<endl;
    cout<<"                     ,---.           ,---.   "<<endl;
    cout<<"                    / /^`.\\.--''''-./,'^\\ \\	"<<endl;
    cout<<"                    \\ \\    _       _    / /	"<<endl;
    cout<<"                     `./  / __   __ \\  \\,'	"<<endl;
    cout<<"                      /    /_O)_(_O\\    \\	"<<endl;
    cout<<"                      |  .-'  ___  `-.  |	"<<endl;
    cout<<"                   .--|       \\_/       |--.	"<<endl;
    cout<<"                 ,'    \\   \\   |   /   /    `."<<endl;
    cout<<"                /       `.  `--^--'  ,'       \\"<<endl;
    cout<<"             .-^^^^^-.    `--.___.--'     .-^^^^^-."<<endl;
    cout<<".-----------/         \\------------------/         \\--------------."<<endl;
    cout<<"| .---------\\         /----------------- \\         /------------. |"<<endl;
    cout<<"| |          `-`--`--'                    `--'--'-'             | |"<<endl;
    cout<<"| |           Welcome to Spell Checker and Dictionary           | |"<<endl;
    cout<<"| |             Enter a word to check it's spelling             | |"<<endl;
    cout<<"| |                  and find it's definition                   | |"<<endl;
    cout<<"| |                                                             | |"<<endl;
    
    if (mode == COMPARISON) {
    cout<<"| |     Current Mode: Comparison                                | |"<<endl;
    } else if (mode == AVL) {
    cout<<"| |     Current Mode: AVL Tree                                  | |"<<endl;
    } else if (mode == TRIE){
    cout<<"| |     Current Mode: Trie                                      | |"<<endl;
    }

    cout<<"| |                                                             | |"<<endl;
    cout<<"| |       Type \"/mode avl\"        for AVL Tree Mode             | |"<<endl;
    cout<<"| |       Type \"/mode trie\"       for Trie Mode                 | |"<<endl;
    cout<<"| |       Type \"/mode comparison\" for Comparison Mode           | |"<<endl;
    cout<<"| |_____________________________________________________________| |"<<endl;
    cout<<"|_________________________________________________________________|"<<endl;
    cout<<"                   )__________|__|__________("<<endl;
    cout<<"                  |            ||            |"<<endl;
    cout<<"                  |____________||____________|"<<endl;
    cout<<"                    ),-----.(      ),-----.("<<endl;
    cout<<"                  ,'   ==.   \\    /  .==    `."<<endl;
    cout<<"                 /            )  (            \\"<<endl;
    cout<<"                 `==========='    `==========='  "<<endl << endl;
    cout << "> ";
}

int main() {
    auto start = chrono::system_clock::now();
    AVL_Tree *avl = read_dict<AVL_Tree>("dictionary.csv");
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << fixed << setprecision(6) << "AVL Tree loaded in " << elapsed_seconds.count() << "s" << endl;

    start = chrono::system_clock::now();
    Trie *trie = read_dict<Trie>("dictionary.csv");
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Trie loaded in " << elapsed_seconds.count() << "s" << endl;

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
            vector<string> definitions;
            vector<string> closest;
            if (mode != TRIE) {
                cout<<"                     ,---.           ,---.   "<<endl;
                cout<<"                    / /^`.\\.--''''-./,'^\\ \\	"<<endl;
                cout<<"                    \\ \\    _       _    / /	"<<endl;
                cout<<"                     `./  / __   __ \\  \\,'	"<<endl;
                cout<<"                      /    /_O)_(_O\\    \\	"<<endl;
                cout<<"                      |  .-'  ___  `-.  |	"<<endl;
                cout<<"                   .--|       \\_/       |--.	"<<endl;
                cout<<"                 ,'    \\   \\   |   /   /    `."<<endl;
                cout<<"                /       `.  `--^--'  ,'       \\"<<endl;
                cout<<"             .-^^^^^-.    `--.___.--'     .-^^^^^-."<<endl;
                cout<<".-----------/         \\------------------/         \\-----------."<<endl;
                cout<<"| .---------\\         /----------------- \\         /---------. |"<<endl;
                cout<<"| |          `-`--`--'                    `--'--'-'          | |"<<endl;
                cout<<"| |   AVL Tree                                               | |"<<endl;
                cout<<"| |                                                          | |"<<endl;
                cout<<"| |   ";
                closest = avl->spell_check(input);
                cout<<"                    | |" << endl;

                if (input != closest[0]) {
                    cout<<"| |   Word Not Found                                         | |"<<endl;
                } else {
                    cout<<"| |   Word Found                                             | |"<<endl;
                    
                    start = chrono::system_clock::now();
                    definitions = avl->definition(input);
                    end = chrono::system_clock::now();
                    elapsed_seconds = end - start;

                    cout << "| |   Definition found in:      " << elapsed_seconds.count() << "s                    | |" << endl;
                }
                if (mode == AVL) {
                    cout<<"| |__________________________________________________________| |"<<endl;
                    cout<<"|______________________________________________________________|"<<endl;
                    cout<<"                   )__________|__|__________("<<endl;
                    cout<<"                  |            ||            |"<<endl;
                    cout<<"                  |____________||____________|"<<endl;
                    cout<<"                    ),-----.(      ),-----.("<<endl;
                    cout<<"                  ,'   ==.   \\    /  .==    `."<<endl;
                    cout<<"                 /            )  (            \\"<<endl;
                    cout<<"                 `==========='    `==========='  "<<endl << endl;
                }
            }
            if (mode != AVL) {
                if (mode == TRIE) {
                    cout<<"                     ,---.           ,---.   "<<endl;
                    cout<<"                    / /^`.\\.--''''-./,'^\\ \\	"<<endl;
                    cout<<"                    \\ \\    _       _    / /	"<<endl;
                    cout<<"                     `./  / __   __ \\  \\,'	"<<endl;
                    cout<<"                      /    /_O)_(_O\\    \\	"<<endl;
                    cout<<"                      |  .-'  ___  `-.  |	"<<endl;
                    cout<<"                   .--|       \\_/       |--.	"<<endl;
                    cout<<"                 ,'    \\   \\   |   /   /    `."<<endl;
                    cout<<"                /       `.  `--^--'  ,'       \\"<<endl;
                    cout<<"             .-^^^^^-.    `--.___.--'     .-^^^^^-."<<endl;
                    cout<<".-----------/         \\------------------/         \\-----------."<<endl;
                    cout<<"| .---------\\         /----------------- \\         /---------. |"<<endl;
                    cout<<"| |          `-`--`--'                    `--'--'-'          | |"<<endl;
                    cout<<"| |   Trie                                                   | |"<<endl;
                    cout<<"| |                                                          | |"<<endl;
                } else {
                    cout<<"| |__________________________________________________________| |"<<endl;
                    cout<<"| |                                                          | |"<<endl;
                    cout<<"| |   Trie                                                   | |"<<endl;
                    cout<<"| |                                                          | |"<<endl;
                }
                cout<<"| |   ";
                closest = trie->spell_check(input);
                cout<<"                    | |" << endl;

                if (input != closest[0]) {
                    cout<<"| |   Word Not Found                                         | |"<<endl;
                } else {
                    cout<<"| |   Word Found                                             | |"<<endl;
                    
                    start = chrono::system_clock::now();
                    definitions = avl->definition(input);
                    end = chrono::system_clock::now();
                    elapsed_seconds = end - start;

                    cout << "| |   Definition found in:      " << elapsed_seconds.count() << "s                    | |" << endl;
                }
                cout<<"| |__________________________________________________________| |"<<endl;
                cout<<"|______________________________________________________________|"<<endl;
                cout<<"                   )__________|__|__________("<<endl;
                cout<<"                  |            ||            |"<<endl;
                cout<<"                  |____________||____________|"<<endl;
                cout<<"                    ),-----.(      ),-----.("<<endl;
                cout<<"                  ,'   ==.   \\    /  .==    `."<<endl;
                cout<<"                 /            )  (            \\"<<endl;
                cout<<"                 `==========='    `==========='  "<<endl << endl;
            }

            cout << "Definitions:" << endl;
            for (int i = 0; i < min((int)definitions.size(), 5); ++i) {
                cout << definitions[i] << endl;
            }
            cout << endl;

            if (input != closest[0]) {
                cout << "Did you mean: ";
                for (auto word : closest) {
                    cout << word << ' ';
                }
                cout << endl;
            }
        }
        getline(cin, input); // buffer
        menu(mode);
        getline(cin, input);
    }
}