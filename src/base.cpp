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
#include <ctime>
#include <sstream>

//set namespace
using namespace std;


//create defenition for transaction object
class Transaction {

    //initialize variables
    string sender;      //who is sending the currency
    string receiver;    //who is recieving it
    int amount;         //the amount being processed
    time_t current_time;//Time transaction last updated
public:

    //Constructor, initialize default values
    Transaction(string from = "", string to = "", int amount = -1) {
        sender = from;
        receiver = to;
        this->amount = amount;
        current_time=time(NULL);
    }

    //accessor of the amount in the transaction
    int getAmount () {
        return amount;
    }
    //modifier for the amount in the transaction
    void setAmount (int amount) {
        this->amount = amount;
        current_time=time(NULL);
    }


    //accessor for the sender of the transaction
    string getSender() {
        return sender;
    }
    //modifier for the sender of the transaction
    void setSender(string from) {
        sender = from;
        current_time=time(NULL);
    }


    //accessor for the reciever of the transaction
    string getReceiver() {
        return receiver;
    }
    //modifier of the reciever of the transaction
    void setReceiver(string to) {
        receiver = to;
        current_time=time(NULL);
    }


    //get the transaction in a string
    string getTransaction() {
        return "From: " + sender + ", To: " + receiver+ ", Amount: " + to_string(amount) + ", " + to_string(current_time);
    }


    //return the hash of the transaction
    string getHash() {
        return sha256(sender+receiver+to_string(amount)+to_string(current_time));
    }

};

//create the class definition for the object block (i.e. what stores the transactions)
class Block {

    //initialize variables
    string previousHash;            //Hash from the previous block
    list <Transaction> transactions;//List of transactions contained in this block
    int difficulty;                 //The difficulty of the block
//    string currentHash;
    time_t timeFound;               //Time the block was last hashed
    list <int> triedFillers;        //list of tried fillers (currently disabled [i think] because of memory problems)
    list <string> fillerHashes;     //list of filler hashed (currently disabled because of memory problems most likely)
    int filler = 0;                 //current filler
    bool found = false;             //If the block hash has been found
    string hash;                    //the current hash

public:

    //Constructor
    Block () {
    }


    //Check if a hash has already been found
    bool foundHash() {
        return found;
    }

    //get the current filler
    int getFiller() {
        return filler;
    }

    //Get the last time the block was sucessfully found
    time_t getTimeFound() {
        return timeFound;
    }

    /* //Not needed right now
    vector <string> getFillerHashResults() {
        vector <string > vecOfStr(fillerHashes.begin(), fillerHashes.end());
        return vecOfStr;
    }

    vector <int> triedFillerHashes() {
        vector <int> vecOfStr(triedFillers.begin(), triedFillers.end());
        return vecOfStr;
    }
     */

    //Get difficulty of block
    int getDifficulty() {
        return difficulty;
    };
    //Set the difficulty of the block (and reset if the block has been found)
    void setDifficulty(int difficulty) {
        found = false;
        this->difficulty = difficulty;
    };

    
    //Set the previous hash of the block (and reset if the block has been found)
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
//            if (!triedFillers.empty()) {
            filler = 0;
//            while (!triedFillers.empty()) {
//                triedFillers.pop_front();
//            }
//            while (!fillerHashes.empty()) {
//                fillerHashes.pop_front();
//            }
//            }
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
            string diff2 = "";
            for (int i = 0; i < sha256("test").length()/diff.length(); i++) {
                diff2+=diff;
            }
            cout << diff2 << "\n";
            while (sha256(all + to_string(filler)) < diff2) {
//                triedFillers.push_back(filler);
//                fillerHashes.push_back(sha256(all + to_string(filler)));
                filler++;
            }

            timeFound = time(NULL);
            hash = sha256(all + to_string(filler));
            found = true;
        }
        return hash;

    }
    string forceFindNewHash() {
        found = false;
        return getHash();
    }
};

class BlockChain {
    list <Block> chain;
//    int length = 0;
    int difficulty = 100000000;
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
        hashCurrentBlock();
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
