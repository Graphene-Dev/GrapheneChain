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

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "block.h"
#include "blockChain.h"
#include "transaction.h"
#include <algorithm>

//set namespace
using namespace std;

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
                vector<Transaction> aT = current.getTransactions();
                cout << "Transactions:\n";
                for (unsigned int j = 0; j < aT.size(); j++) {
                    cout << i << ". " << aT.at(i).getTransaction() << "\n";
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
            for (unsigned int i = 0; i < a.size(); i++) {
                cout << i + 1 << ". " << a.at(i).getTransaction() << "\n";
            }
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
        if (input == "currentHashBlock") {
            Block current = chain.getCurrentBlockHashed();
            cout << "Previous Hash: " << current.getPreviousHash() << "\n";
            vector<Transaction> a = current.getTransactions();
            cout << "Transactions:" << "\n";
            for (unsigned int i = 0; i < a.size(); i++) {
                cout << i + 1 << ". " << a.at(i).getTransaction() << "\n";
            }
            if (current.foundHash()) {
                cout << "Block Hash: ";
                cout << current.getHash() << "\n";
            }
            cout << "Difficulty: " << current.getDifficulty() << "\n";
            cout << "Current Filler tested: " << current.getFiller() << "\n";
//            cout << "Found date: " << to_string(block.getTimeFound());
            cout << "\n";
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
