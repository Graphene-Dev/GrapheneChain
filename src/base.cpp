#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "sha256.h"
using namespace std;

class Transaction {
    string sender;
    string receiver;
    int amount;
//    string date;
public:
    Transaction(string from, string to, int amount) {
        sender = from;
        receiver = to;
        this->amount = amount;
    }
    int getAmount () {
        return amount;
    }
    void setAmount (int amount) {
        this->amount = amount;
    }

    string getSender() {
        return sender;
    }
    void setSender(string from) {
        sender = from;
    }

    string getReceiver() {
        return receiver;
    }
    void setReceiver(string to) {
        receiver = to;
    }

    string getTransaction() {

    }

    string getHash() {
        
    }
    
};

class Block {
    string previousHash = "";
    list <string> transactions;

public:
    Block () {
    }

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
        string* transactions = new string[this->transactions.size()];
        int k = 0;
        for (string const &i: this->transactions) {
            transactions[k++] = i;
        }
        for (unsigned int i = 0; i < this->transactions.size(); i++) {
            transactiosnHashed.push_back(sha256(to_string(i)+transactions[i]));
        }
        string* transactionsHashes = new string[transactiosnHashed.size()];
        int l = 0;
        for (string const &i: transactiosnHashed) {
            transactionsHashes[l++] = i;
        }
        string all = previousHash;
        for (unsigned int i = 0; i < transactiosnHashed.size(); i++) {
            all += "\n" + transactionsHashes[i];
        }
        return sha256(all);
    }

};

class BlockChain {
    static list <Block> chain;
    int length = 0;

public:
    BlockChain() {
    }
    void addBlock(Block newBlock) {
        chain.push_back(newBlock);
    }

    void removeBlock() {
        cout << "Not implemented yet \n";
    }

    bool verifyChain(int start = 0, int end = chain.size()) { //doesnt include end
        Block* blocks = new Block[chain.size()];
        int l = 0;
        for (Block const &i: chain) {
            blocks[l++] = i;
        }

        string currentHash = blocks[start].getHash();
        for (int i = start+1; i < end; i++) {
            if (currentHash != blocks[i].getPreviousHash()) {
                return false;
            }
            currentHash = blocks[i].getHash();
        }
        return true;

    }

    vector<Block> getBlocks() {
        vector <Block> vecOfStr(chain.begin(), chain.end());
        return vecOfStr;
    }
};

int main(int argc, char *argv[]) {
    cout << "Base Start\n";
    //Content

    BlockChain chain;
    while (true) {
        cout << "Next action?";
        string input;
        cin >> input;
        if (input == "exit") {
            break;
        }
        if (input == "newBlock") {

        }
        if (input == "newTransaction") {

        }
        if (input == "displayChain") {

        }
        if (input == "displayCurrentBlock") {

        }
    }


    cout << "Base End\n";
    return 0;
}



