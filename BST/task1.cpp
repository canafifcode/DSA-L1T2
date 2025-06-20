#include <iostream>
#include <fstream>
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
        return 2;
    }
    char c, str[5];
    int val;
    BST<int, int> *bst = new ListBST<int, int>();
    if (!bst) {
        cerr << "Memory allocation failed\n";
        return 3;
    }
    while (in_file >> c) {
        // TODO: Implement the logic to read commands from the file and output accordingly
        // After every insertion and removal, print the BST in nested parentheses format
        // Handle exceptions where necessary and print appropriate error messages
        // Start your code here
        if(c=='I'){
            int key, value;
            in_file >> key;
            value= key;
            if (bst->insert(key, value)) {
                cout << "Key "<<key <<" inserted into BST, BST (Default): " ;
            } 
            else {
                cout << "Insertion failed! Key " << key << " already exists in BST, BST (Default): ";
            }
            //(8:8 (1:1 () (6:6 (4:4)))(10:10 () (14:14)))
            bst->print('D');
            cout<<endl;
        }
        else if(c=='D'){
            int key;
            in_file >> key;
            if (bst->remove(key)) {
                cout << "Key " << key << " removed from BST, BST (Default): ";
            } 
            else {
                cout << "Removal failed! Key "<< key<< " not found in BST, BST (Default): " ;
            }
            bst->print('D');
            cout<<endl;
        }
        else if(c=='M'){
            string s;
            in_file >> s;
            if(s =="Min"){
                try{
                    int min_key = bst->find_min();
                    cout << "Minimum value: " << min_key << endl;
                } catch (const std::runtime_error &e) {
                    cout << e.what() << endl;
                }
            }
            else if(s =="Max"){
                try{
                    int max_key = bst->find_max();
                    cout << "Maximum value: " << max_key << endl;
                } catch (const std::runtime_error &e) {
                    cout << e.what() << endl;
                }
            }
        }
        else if(c=='F'){
            int key;
            in_file >> key;
            if (bst->find(key)) {
                cout << "Key " << key << " found in BST." << endl;
            } 
            else {
                cout << "Key " << key << " not found in BST." << endl;
            }
        }
        else if(c=='T'){
            string tt;
            in_file >> tt;
            if (tt == "In") {
                cout << "BST (In-order): ";
                bst->print('I');
            }
            else if (tt == "Pre") {
                cout << "BST (Pre-order): ";
                bst->print('P');
            }
            else if (tt == "Post") {
                cout << "BST (Post-order): ";
                bst->print('O');
            }
            else {
                cout << "Invalid traversal type. Use 'In', 'Pre', or 'Post'." << endl;
            }
            cout<<endl;
        }
        else if(c=='S'){
            cout<< "Size: "<<bst->size()<<endl;
        }
        else if(c=='E'){
            if(bst->empty()){
                cout<<"Empty"<<endl;
            }
            else{
                cout<<"Not Empty"<<endl;
            }
        }
        else if(c=='C'){
            bst->clear();
            cout<<"BST cleared";
            cout<<endl;
        }
        else{
            cout<<"Invalid command"<<endl;
        }

        // End your code here
    }
    in_file.close();
    delete bst;
    return 0;
}

