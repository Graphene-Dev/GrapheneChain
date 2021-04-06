/*
 *  Created by StealthHydra179 and TechyGuy17
 *
 * If you found this code useful please donate here:
 *
 * This code is distributed under the GPL 3 license, to read it refer to https://github.com/Graphene-Dev/GrapheneChain/blob/master/LICENSE . if you find an error put it in
 * the errors page on GitHub
 *
 * Thank you
 */


#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "sha256.h"
using namespace std;

class Transaction {
    string sender;
    string receiver;
    int amount;
public:
    Transaction(string from = "", string to = "", int amount = -1) {
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
    int difficulty;
    string currentHash = getHash();
public:
    Block () {
    }
    int getDifficulty() {
        return difficulty;
    };
    void setDifficulty(int difficulty) {
        this->difficulty = difficulty;
    };
    void setPreviousHash(string previousHash) {
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

        Transaction* transactionsHashes = new Transaction[this->transactions.size()];
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
    //  void correctHash() {
    //     if(currentHash <)
    // }
    // Work in progress

};

class BlockChain {
    list <Block> chain;
//    int length = 0;
    int difficulty;
    int hashrate = 1000;

public:
    BlockChain() {
    }
   int getDifficulty() {
       return difficulty;
    }

    void addBlock(Block newBlock) {
        chain.push_back(newBlock);
        difficulty = hashrate^2;
    }

    void removeBlock() {
        cout << "Not implemented yet \n";
    }

    bool verifyChain(int start = 0, int end = -1) { //doesnt include end
        if (end == -1) {
            end = chain.size();
        }
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



BlockChain chain;
Block block;


void userActions() {
    while (true) {
        cout << "Next action? ";
        string input;
        cin >> input;
        if (input == "exit") {
            break;
//cout << "test";
        }
        if (input == "newBlock") {
            chain.addBlock(block);
            string hash = block.getHash();
            block = *new Block;
            block.setPreviousHash(hash);
            block.setDifficulty(chain.getDifficulty());
            cout << "The current difficulty is " << block.getDifficulty() << "\n";
        }
        if (input == "newTransaction") {
            string from;
            string to;
            int amount;
            cout << "From?";
            cin >> from;
            cout << "To?";
            cin >> to;
            cout << "Amount?";
            cin >> amount;
            Transaction newTransaction(from, to, amount);
            block.addTransaction(newTransaction);
        }
        if (input == "displayChain") {
            vector<Block> a = chain.getBlocks();
            for(unsigned int i=0; i < a.size(); i++) {
                Block current = a.at(i);
                cout << "Block " << i+1;
                cout << "\n";
                cout << "Previous Hash: " << current.getPreviousHash();
                cout << "\n";
                vector<Transaction> a = current.getTransactions();
                cout << "Transactions:\n";
                for(unsigned int i=0; i < a.size(); i++)
                    cout << i << ". " << a.at(i).getTransaction() << "\n";
                cout << "Hash: " << current.getHash() << "\n";
                cout << "diff: " << block.getHash() << "\n";
                cout << "\n";
            }
        }
        if (input == "displayCurrentBlock") {
            cout << "Hash: " << block.getPreviousHash() << "\n";
            vector<Transaction> a = block.getTransactions();
            for(unsigned int i=0; i < a.size(); i++)
                cout << i+1 << ". " << a.at(i).getTransaction() << "\n";
            cout << block.getHash();
            cout << "\n";
        }
    }
}

int main(int argc, char *argv[]) {
    cout << "Base Start\n";
    //Content
    block.setPreviousHash("");
//    try {
    thread thread_obj(userActions);
//    } catch  (exception e){
//        cout << e.what();
//    }


    thread_obj.join();

    cout << "Base End\n";

    return 0;
}
