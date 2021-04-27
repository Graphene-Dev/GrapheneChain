

#ifndef GRAPHENECHAIN_BLOCK_H
#define GRAPHENECHAIN_BLOCK_H

#endif //GRAPHENECHAIN_BLOCK_H

using namespace std;

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "sha256.h"
#include "block.h"
#include "blockChain.h"
#include "transaction.h"
#include <ctime>
#include <sstream>
#include <algorithm>
#include "Transaction.h"


//create the class definition for the object block (i.e. what stores the transactions)
class Block {
    //initialize variables
    string previousHash;            //Hash from the previous block
    list<Transaction> transactions;//List of transactions contained in this block
    unsigned long difficulty;                 //The difficulty of the block
//    string currentHash;
    time_t timeFound;               //Time the block was last hashed
    list<int> triedFillers;        //list of tried fillers (currently disabled [i think] because of memory problems)
    list<string> fillerHashes;     //list of filler hashed (currently disabled because of memory problems most likely)
    long filler = 0;                 //current filler
    bool found = false;             //If the block hash has been found
    string hash;                    //the current hash


    bool hex_greater(basic_string<char, char_traits<char>, allocator<char>> first, std::string &second) {
        while (first.at(0) == '0') {
            first = first.substr(1, first.length());
        }
        while (second.at(0) == '0') {
            second = second.substr(1, second.length());
        }
        /* Comprasions based on size */
        int firstSize = first.size();
        int secondSize = second.size();
        if (firstSize > secondSize)
            return true;
        else if (firstSize < secondSize)
            return false;

        /* Convert to lower case, for case insentitive comprasion */
        transform(first.begin(), first.end(), first.begin(), ::tolower);
        transform(second.begin(), second.end(), second.begin(), ::tolower);

        /* Call the std::string operator>(...) which compare strings lexicographically */
        if (first > second)
            return true;
        /* In other cases first hex string is not greater */
        return false;
    }

public:
    //Constructor
    Block() {
    }


    //Check if a hash has already been found
    bool foundHash();

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
    unsigned long getDifficulty() {
        return difficulty;
    };

    //Set the difficulty of the block (and reset if the block has been found)
    void setDifficulty(unsigned long difficulty) {
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
        vector<Transaction> vecOfStr(transactions.begin(), transactions.end());
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

            string all = previousHash + "|";
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
            string temp = all;
            while (difficulty != 0 && hex_greater(sha256(temp), diff)) {
//                triedFillers.push_back(filler);
//                fillerHashes.push_back(sha256(all + to_string(filler)));
                temp = all + to_string(filler);
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