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

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "sha256.h"
#include <ctime>
#include <sstream>
using namespace std;

class Transaction {
    string sender;
    string receiver;
    int amount;
    time_t current_time = time(NULL);
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
    time_t timeFound;
    list <int> triedFillers;
    list <string> fillerHashes;
    int filler = 0;
    bool found = false;
    string hash;

public:
    Block () {
    }

    bool foundHash() {
        return found;
    }

    int getFiller() {
        return filler;
    }

    vector <string> getFillerHashResults() {
        vector <string > vecOfStr(fillerHashes.begin(), fillerHashes.end());
        return vecOfStr;
    }

    vector <int> triedFillerHashes() {
        vector <int> vecOfStr(triedFillers.begin(), triedFillers.end());
        return vecOfStr;
    }

    int getDifficulty() {
        return difficulty;
    };
    void setDifficulty(int difficulty) {
        found = false;
        this->difficulty = difficulty;
    };

    void setPreviousHash(string previousHash) {
        found = false;
        this->previousHash = previousHash;
    }
    string getPreviousHash() {
        return previousHash;
    }

    void addTransaction(Transaction transaction) {
        found = false;
        this->transactions.push_back(transaction);
    }
    void removeTransaction(int position) {
        cout << "Not implemented yet \n";
    }

    vector<Transaction> getTransactions() {
        vector <Transaction > vecOfStr(transactions.begin(), transactions.end());
        return vecOfStr;
    }

    string getHash() {
        if (!found) {
            triedFillers.clear();
            fillerHashes.clear();

            Transaction *transactionsHashes = new Transaction[this->transactions.size()];
            int l = 0;
            for (Transaction const &i: this->transactions) {
                transactionsHashes[l++] = i;
            }

            string all = previousHash;
            for (unsigned int i = 0; i < this->transactions.size(); i++) {
                all += "\n" + transactionsHashes[i].getHash();
            }

            stringstream ss;
            ss << hex << difficulty;
            string diff = ss.str();
            while (sha256(all + to_string(filler)) < diff) {
                triedFillers.push_back(filler);
                fillerHashes.push_back(sha256(all + to_string(filler)));
                filler++;
            }

            timeFound = time(NULL);
            hash = sha256(all);

            return sha256(all);

        } else {
            return hash;
        }
    }
    string forceFindNewHash() {
        found = false;
        return getHash();
    }
};

class BlockChain {
    list <Block> chain;
//    int length = 0;
    int difficulty = 10000;
    int hashrate = 1000;
    int targetTime = 10; //in seconds
    Block currentHashedBlock;
    bool blockHashed = true;
    bool ready = true;
    string projectName;
    string projectNameHash;

    void setDifficulty() {

    }
    void hashCurrentBlock() {
        if (!blockHashed && !ready) {
            currentHashedBlock.getHash();
            blockHashed = true;
        }
    }

public:
    BlockChain() {
    }

    void setTargetTime(int target) {
        targetTime = target;
    }
    int getTargetTime() {
        return targetTime;
    }

    int getDifficulty() {
        return difficulty;
    }

    Block getCurrentBlockHashed() {
        return currentHashedBlock;
    }

    bool getBlockhashed() {
        return blockHashed;
    }
    void pushBlock() {
        if (blockHashed) {
            chain.push_back(currentHashedBlock);
            setDifficulty();
            ready = true;
        }
    }


    void addBlock(Block newBlock) {
        blockHashed = false;
        ready = false;
        currentHashedBlock = newBlock;
//        difficulty = hashrate*hashrate;
        thread threadobj(hashCurrentBlock());
        threadobj.join();
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
            if (!blocks[i].foundHash()) {
                return false;
            }
            currentHash = blocks[i].getHash();
        }
        return true;

    }
    void setProjectNameHash (string projectName, string projectNameHash) {
      this-> projectName = "GrapheneChain"; //Change this to your cryptos name
      this-> projectNameHash = sha256(projectName);
        
    }
    void setProjectNameHash(string projectNameHash) {
        this->projectNameHash = projectNameHash;
       
    }
    string getProjectNameHash() {
        return projectNameHash; 
       
    }


    vector<Block> getBlocks() {
        vector <Block> vecOfStr(chain.begin(), chain.end());
        return vecOfStr;
    }
};



BlockChain chain;
Block block;
bool running = true;

void userActions() {
    while (true) {
        cout << "Next action? ";
        string input;
        cin >> input;
        if (input == "exit") {
            running = false;
            break;
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
//            cout << "project hash: " << chain.getProjectNameHash() << "\n";
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
                cout << "diff: " << current.getDifficulty() << "\n";

                cout << "\n";
            }
        }
        if (input == "displayCurrentBlock") {
            cout << "Previous Hash: " << block.getPreviousHash() << "\n";
            vector<Transaction> a = block.getTransactions();
            cout << "Transactions:" << "\n";
            for(unsigned int i=0; i < a.size(); i++)
                cout << i+1 << ". " << a.at(i).getTransaction() << "\n";
            cout << "Block Hash: ";
            cout << block.getHash();
            cout << "\n";
        }
      
    }
}

int main() {
    cout << "Base Start\n";
//    //Content
    block.setPreviousHash("");
    thread thread_obj(userActions);
    while (running) {
        if (chain.getBlockhashed()) {
            chain.pushBlock();
            chain.addBlock(block);
            string hash = block.getHash();
            block = *new Block;
            block.setPreviousHash(hash);
            block.setDifficulty(chain.getDifficulty());
        }
    }
    thread_obj.join();

    cout << "Base End\n";

    return 0;
}
