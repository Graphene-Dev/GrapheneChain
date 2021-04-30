/*
 *  Created by StealthHydra179 and TechyGuy17
 *
 * If you found this code useful please donate here:
 *https://www.patreon.com/GrapheneDev
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
#include "sha256.h"
#include "blockChain.h"
#include "transaction.h"
#include "block.h"

//set namespace
using namespace std;


BlockChain chain;
Block block;

bool running = true;

void userActions() {
    while (true) {
        cout << "The availible commands are: \n newTransacion \n displayChain \n displayCurrentBlock \n hashblock (OBS! only for testing) \n";
        cout << "\n";
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
        if (input == "hashBlock") {
            cout << "hashing block" << "\n";
            chain.addBlock(block);
             if (block.foundHash()) {
                cout << "Block Hash: ";
                cout << block.getHash() << "\n";
            }
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
            vector<Block> blocksList = chain.getBlocks();
//            cout << "1";
            chain.pushBlock();
//            cout << "2";
            if (blocksList.size() > 2) {
                block.setPreviousHash(blocksList.at((blocksList.size() - 1)).getHash());
            }
//            cout << "3";
            chain.addBlock(block);
//            cout << "4";
            block = *new Block;
//            cout << "5";
            block.setDifficulty(chain.getDifficulty());
//            cout << "6";
        }
    }
    thread_obj.join();

    cout << "Base End\n";

    return 0;
}
