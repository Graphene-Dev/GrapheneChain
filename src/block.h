#ifndef GRAPHENECHAIN_BLOCK_H
#define GRAPHENECHAIN_BLOCK_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "sha256.h"
#include "transaction.h"
#include <ctime>
#include <sstream>
#include <algorithm>

using namespace std;

//create the class definition for the object block (i.e. what stores the transactions)
class Block {
    //initialize variables
    string previousHash;            //Hash from the previous block
    list<Transaction> transactions;//List of transactions contained in this block
    int diffPadding;
    unsigned long long difficulty;                 //The difficulty of the block
//    string currentHash;
    time_t timeFound;               //Time the block was last hashed
//    list<int> triedFillers;        //list of tried fillers (currently disabled [i think] because of memory problems)
//    list<string> fillerHashes;     //list of filler hashed (currently disabled because of memory problems most likely)
    long filler = 0;                 //current filler
    bool found = false;             //If the block hash has been found
    string hash;                    //the current hash
    int adjustmentFactor = 1;       //difficulty adjustment factor
    static unsigned long long numberOfBlocks;
    int currentBlock;



public:
    //Constructor
    Block() {
        currentBlock = numberOfBlocks;
        numberOfBlocks++;
    }

    bool hex_greater(basic_string<char, char_traits<char>, allocator<char>> first, std::string &second);

    //Check if a hash has already been found
    bool foundHash();

    //get the current filler
    long getFiller();

    //Get the last time the block was sucessfully found
    time_t getTimeFound();

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
    unsigned long getDifficulty();

    //Set the difficulty of the block (and reset if the block has been found)
    void setDifficulty(unsigned long difficulty);


    //Set the previous hash of the block (and reset if the block has been found)
    void setPreviousHash(string previousHash);

    //Accessor of the previous hash that is defined in the block
    string getPreviousHash();

    //Add a transaction (and reset if the block has been found)
    void addTransaction(Transaction transaction);

    //Remove a transaction (incomplete)
    void removeTransaction(int position);

    //Get the transactions in the list
    vector<Transaction> getTransactions();

    //Get the current Hash or create a hash for the block
    string getHash();

    //Force the program to find a new hash
    string forceFindNewHash();


    int getDiffPadding();

    void setDiffPadding(int padding);

    string toString();




};

ostream& operator<<(ostream& out, Block& b);
#endif //GRAPHENECHAIN_BLOCK_H