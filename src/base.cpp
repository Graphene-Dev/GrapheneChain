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
        return "From: " + sender + ", To: " + receiver+ ", Amount: " + to_string(amount);
    }

    string getHash() {
        return sha256(sender+receiver+to_string(amount));
    }
    
};

class Block {
    string previousHash;
    list <Transaction> transactions;

public:
    Block () {
    }

    void setPreviousHash(Transaction previousHash) {
        this->previousHash = previousHash;
    }

    void addTransaction(Transaction transaction) {
        this->transactions.push_back(transaction);
    }

    void removeTransaction(int position) {
        cout << "Not implemented yet \n";
    }

    vector<Transaction> getTransactions() {
        vector <Transaction > vecOfStr(transactions.begin(), transactions.end());
        return vecOfStr;
    }

    string getPreviousHash() {
        return previousHash;
    }

    string getHash() {

        Transaction* transactionsHashes = new string[this->transactions.size()];
        int l = 0;
        for (Transaction const &i: this->transactions) {
            transactionsHashes[l++] = i;
        }
        string all = previousHash;
        for (unsigned int i = 0; i < this->transactions.size(); i++) {
            all += "\n" + transactionsHashes[i].getHash();
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



