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
    string previousHash = "";
    list <string> transactions;

public:
    Block () {}

    void setPreviousHash(string previousHash) {
        this->previousHash = previousHash;
    }

    void addTransaction(string transaction) {
        this->transactions.push_back(transaction);
    }

    void removeTransaction(int position) {
        cout << "Not implemented yet \n";
    }

    vector<string> getTransactions() {
       vector <string > vecOfStr(transactions.begin(), transactions.end());
       return vecOfStr;
    }

    string getPreviousHash() {
        return previousHash;
    }

    string getHash() {
        list <string> transactiosnHashed;
        string transactions[transactions.size()];
        int k = 0;
        for (string const &i: this->transactions) {
            transactions[k++] = i;
        }
        for (int i = 0; i < transactions.size(); i++) {
            transactiosnHashed.push_back(sha256(to_string(i)+transactions[i]));
        }
        string transactionsHashes[transactions.size()];
        int l = 0;
        for (string const &i: transactiosnHashed) {
            transactionsHashes[l++] = i;
        }
        string all = previousHash;
        for (int i = 0; i < transactiosnHashed.size(); i++) {
            all += "\n" + transactionsHashes[i];
        }
        return sha256(all);
    }

};