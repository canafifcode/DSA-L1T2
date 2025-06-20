#include <iostream>
#include <fstream>
#include <string>
#include "listBST.hpp"
using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file) {
        cerr << "Unable to open file\n";
        return 1;
    }

    BST<string, int> *bst1 = new ListBST<string, int>();
    if (!bst1) {
        cerr << "Memory allocation failed\n";
        return 2;
    }
    BST<string, int> *bst2 = new ListBST<string, int>();
    if (!bst2) {
        cerr << "Memory allocation failed\n";
        delete bst1; // Clean up previously allocated memory
        return 3;
    }

    int n;
    in_file >> n;
    for (int i = 0; i < n; ++i) {
        // TODO: Implement the logic to read Phil's words
        // Start your code here
        string phil;
        // where the key is a word (string) and the value is the count of cards with that word (integer).
        in_file >> phil;
        if(bst1->find(phil)) {
            int count = bst1->get(phil);
            bst1->update(phil, count + 1);
        } else {
            bst1->insert(phil, 1);
        }
        // End your code here
    }
    for (int i = 0; i < n; ++i) {
        // TODO: Implement the logic to read Claire's words
        // Start your code here
        string claire;
        in_file >> claire;
        if(bst2->find(claire)) {
            int count = bst2->get(claire);
            bst2->update(claire, count + 1);
        } else {
            bst2->insert(claire, 1);
        }
        // End your code here
    }

    // TODO: Implement the logic to print the initial state of both hands
    // Start your code here
    cout<< "Phil's words:"<<endl;
    cout<< "BST (In-order): ";
    bst1->print('I');
    cout << endl;
    cout << "\nClaire's words:" << endl;
    cout<< "BST (In-order): ";
    bst2->print('I');
    cout << endl;
    // End your code here
    cout << "\nGame starts!\n\n";
    cout << "==============================\n";

    while (true) {
        string word;
        in_file >> word;
        
        // TODO: Implement the logic to process the game turn and print both hands after each turn
        // Start your code here
        bool philcard = bst1->find(word);
        bool clairecard = bst2->find(word);
        if(philcard){
            int count = bst1->get(word);
            if(count > 1) {
                bst1->update(word, count - 1);
            } else {
                bst1->remove(word);
            }
            cout<< "Phil has "<< word<<"!"<<endl;
        }
        if(clairecard){
            int count = bst2->get(word);
            if(count > 1) {
                bst2->update(word, count - 1);
            } else {
                bst2->remove(word);
            }
            cout<< "Claire has "<< word<<"!"<<endl;
        }
    
        if(bst1->empty()&& bst2->empty()){
            cout<< "The game is a draw!"<<endl;
            break;
        }
        if(bst1->empty()){
            cout<< "Phil wins!"<<endl;
            break;
        }
        if(bst2->empty()){
            cout<< "Claire wins!"<<endl;
            break;
        }
        cout<<endl;
        cout<< "Phil's remaining words:\n";
        cout << "BST (In-order): ";
        bst1->print('I');
        cout << endl;
        cout << "\nClaire's remaining words:\n";
        cout << "BST (In-order): ";
        bst2->print('I');
        cout << endl ;
        cout << endl;


        // End your code here
        cout << "==============================\n";
    }

    in_file.close();
    delete bst1;
    delete bst2;
    return 0;
}