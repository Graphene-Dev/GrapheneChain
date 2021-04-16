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
    long difficulty;                 //The difficulty of the block
//    string currentHash;
    time_t timeFound;               //Time the block was last hashed
    list <int> triedFillers;        //list of tried fillers (currently disabled [i think] because of memory problems)
    list <string> fillerHashes;     //list of filler hashed (currently disabled because of memory problems most likely)
    long filler = 0;                 //current filler
    bool found = false;             //If the block hash has been found
    string hash;                    //the current hash


    bool hex_greater(basic_string<char, char_traits<char>, allocator<char>> first, std::string &second)
    {
        while (first.at(0) == '0') {
            first = first.substr(1,first.length());
        }
        while (second.at(0) == '0') {
            second = second.substr(1,second.length());
        }
        /* Comprasions based on size */
        int firstSize = first.size();
        int secondSize = second.size();
        if(firstSize > secondSize)
            return true;
        else if(firstSize < secondSize)
            return false;

        /* Convert to lower case, for case insentitive comprasion */
        std::transform(first.begin(), first.end(), first.begin(), ::tolower);
        std::transform(second.begin(), second.end(), second.begin(), ::tolower);

        /* Call the std::string operator>(...) which compare strings lexicographically */
        if(first > second)
            return true;

        /* In other cases first hex string is not greater */
        return false;
    }
public:

    //Constructor
    Block () {
    }


    //Check if a hash has already been found
    bool foundHash() {
        return found;
    }

    //get the current filler
    long getFiller() {
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
    long getDifficulty() {
        return difficulty;
    };
    //Set the difficulty of the block (and reset if the block has been found)
    void setDifficulty(long difficulty) {
        found = false;
        this->difficulty = difficulty;
    };


    //Set the previous hash of the block (and reset if the block has been found)
    void setPreviousHash(string previousHash) {
        found = false;
        this->previousHash = previousHash;
    }
    //Accessor of the previous hash that is defined in the block
    string getPreviousHash() {
        return previousHash;
    }

    //Add a transaction (and reset if the block has been found)
    void addTransaction(Transaction transaction) {
        found = false;
        this->transactions.push_back(transaction);
    }
    //Remove a transaction (incomplete)
    void removeTransaction(int position) {
        cout << "Not implemented yet \n";
    }

    //Get the transactions in the list
    vector<Transaction> getTransactions() {
        vector <Transaction > vecOfStr(transactions.begin(), transactions.end());
        return vecOfStr;
    }

    //Get the current Hash or create a hash for the block
    string getHash() {
        if (!found) {
            filler = 0;
            Transaction *transactionsHashes = new Transaction[this->transactions.size()];
            int l = 0;
            for (Transaction const &i: this->transactions) {
                transactionsHashes[l++] = i;
            }

            string all = previousHash;
            for (unsigned int i = 0; i < this->transactions.size(); i++) {
                all += "\n" + transactionsHashes[i].getHash();
            }


            //In the future reverse it so as difficulty goes up, the harder it is ig
            stringstream ss;
            ss << hex << difficulty;
//            cout << difficulty;
            string diff = ss.str();
//            string diff2 = "";
//            diff+=diff;
//            diff+=diff;
//            cout << diff2 << "\n";
            while (difficulty != 0 && hex_greater(sha256(all + to_string(filler)), diff) ) {
//                triedFillers.push_back(filler);
//                fillerHashes.push_back(sha256(all + to_string(filler)));
                filler++;
//                cout << "newhash\n";
//                cout << diff << "\n" << sha256(all + to_string(filler)) << "\n";
//                cout << filler << "\n";
            }


            timeFound = time(NULL);
            hash = sha256(all + to_string(filler));
            found = true;
        }
        return hash;

    }
    //Force the program to find a new hash
    string forceFindNewHash() {
        found = false;
        return getHash();
    }
};

//Block-chain class, contains all of the blocks
class BlockChain {
    list <Block> chain;
//    int length = 0;
    unsigned long difficulty = 9999999999;
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
                for(unsigned int i=0; i < a.size(); i++) {
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
            for(unsigned int i=0; i < a.size(); i++)
                cout << i+1 << ". " << a.at(i).getTransaction() << "\n";
            if (block.foundHash()) {
                cout << "Block Hash: ";
                cout << block.getHash() << "\n";
            }
            cout << "Difficulty: " << block.getDifficulty() << "\n";
//            cout << "Found date: " << to_string(block.getTimeFound());
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
            vector <Block> blocksList = chain.getBlocks();
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
