#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "sha256.h"
using namespace std;

int main(int argc, char *argv[]) {
    cout << "Base Start\n";
    //Content

    cout << "Base End\n";

    string input = "this is a test";
    string hash = sha256(input);

    cout << "sha256('"<< input << "'):" << hash <<  endl;
    return 0;
}


class BlockChain {

public:
    int height;


};

class Block {
    string previousHash;
    list <string> transactions;

public:
    Block () {}

    void setPreviousHash() {

    }

    void addTransaction() {

    }

    void removeTransaction(int position) {
        
    }

    vector<string> getTransactions() {

    }

    string getPreviousHash() {

    }

    string getHash() {

    }

};