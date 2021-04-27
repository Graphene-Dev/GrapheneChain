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

//Include all needed things
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
#include "block.h"
//#include "blockChain.h"
#include "transaction.h"
#include <ctime>
#include <sstream>
#include <algorithm>
//#include "Transaction.h"

//set namespace
using namespace std;




//Block-chain class, contains all of the blocks
class BlockChain {
    list<Block> chain;
//    int length = 0;
    unsigned long difficulty = 9999999999999999;
    int hashrate = 1000;
    int targetTime = 10; //in seconds
    Block currentHashedBlock;
    bool blockHashed = true;
    bool ready = true;
    string projectName;
    string projectNameHash;

    void setDifficulty() {
        /*later*/
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

    unsigned long getDifficulty() {
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
        hashCurrentBlock();
    }

    void removeBlock() {
        cout << "Not implemented yet \n";
    }

    bool verifyChain(int start = 0, int end = -1) { //doesnt include end
        if (end == -1) {
            end = chain.size();
        }
        Block *blocks = new Block[chain.size()];
        int l = 0;
        for (Block const &i: chain) {
            blocks[l++] = i;
        }

        string currentHash = blocks[start].getHash();
        for (int i = start + 1; i < end; i++) {
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

    void setProjectNameHash(string projectName, string projectNameHash) {
        this->projectName = "GrapheneChain"; //Change this to your cryptos name
        this->projectNameHash = sha256(projectName);
    }

    void setProjectNameHash(string projectNameHash) {
        this->projectNameHash = projectNameHash;
    }

    string getProjectNameHash() {
        return projectNameHash;
    }


    vector<Block> getBlocks() {
        vector<Block> vecOfStr(chain.begin(), chain.end());
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
            for (unsigned int i = 0; i < a.size(); i++) {
                Block current = a.at(i);
                cout << "Block " << i + 1;
                cout << "\n";
                cout << "Previous Hash: " << current.getPreviousHash();
                cout << "\n";
                vector<Transaction> a = current.getTransactions();
                cout << "Transactions:\n";
                for (unsigned int i = 0; i < a.size(); i++) {
                    cout << i << ". " << a.at(i).getTransaction() << "\n";
                    if (current.foundHash()) {
                        cout << "Hash: " << current.getHash() << "\n";
                    }
                }
                cout << "diff: " << current.getDifficulty() << "\n";
//                cout << "Found date: " << to_string(current.getTimeFound());
                cout << "\n";
            }
        }
        if (input == "displayCurrentBlock") {
            cout << "Previous Hash: " << block.getPreviousHash() << "\n";
            vector<Transaction> a = block.getTransactions();
            cout << "Transactions:" << "\n";
            for (unsigned int i = 0; i < a.size(); i++)
                cout << i + 1 << ". " << a.at(i).getTransaction() << "\n";
            if (block.foundHash()) {
                cout << "Block Hash: ";
                cout << block.getHash() << "\n";
            }
            cout << "Difficulty: " << block.getDifficulty() << "\n";
//            cout << "Found date: " << to_string(block.getTimeFound());
            cout << "\n";
        }
        //For developing, will be removed later
        if (input == "forceBlock") {
            cout << "Force hashing block" << "\n";
            block.forceFindNewHash();
             if (block.foundHash()) {
                cout << "Block Hash: ";
                cout << block.getHash() << "\n";
            }
        }
    }
}

int main() {
    cout << "Base Start\n";


    block.setPreviousHash("");
    thread thread_obj(userActions);
    while (running) {
        if (chain.getBlockhashed()) {
            chain.pushBlock();

            vector<Block> blocksList = chain.getBlocks();
            if (blocksList.size() > 2) {
                block.setPreviousHash(blocksList.at((blocksList.size() - 1)).getHash());
            }

            chain.addBlock(block);
            block = *new Block();
            block.setDifficulty(chain.getDifficulty());
        }
    }
    thread_obj.join();

    cout << "Base End\n";

    return 0;
}
