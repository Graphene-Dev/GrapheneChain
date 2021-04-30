#include "block.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "sha256.h"
#include "transaction.h"
#include <ctime>
#include <algorithm>

using namespace std;

bool Block::hex_greater(basic_string<char, char_traits<char>, allocator<char>> first, std::string &second) {
    while (first.at(0) == '0') {
        first = first.substr(1, first.length());
    }
    while (second.at(0) == '0') {
        second = second.substr(1, second.length());
    }
    /* Comparisons based on size */
    int firstSize = first.size();
    int secondSize = second.size();
    if (firstSize > secondSize)
        return true;
    else if (firstSize < secondSize)
        return false;

    /* Convert to lower case, for case insensitive comparison */
    transform(first.begin(), first.end(), first.begin(), ::tolower);
    transform(second.begin(), second.end(), second.begin(), ::tolower);

    /* Call the std::string operator>(...) which compare strings lexicographically */
    if (first > second)
        return true;
    /* In other cases first hex string is not greater */
    return false;
}

//Check if a hash has already been found
bool Block::foundHash() {
    return found;
}


string Block::getHash() {

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


        //In the future reverse it so as difficulty goes up, the harder it is
        stringstream ss;
        ss << hex << difficulty;
        string diff = ss.str();
        string temp = all;
        stringstream ss2;
        ss2 << hex << temp;
        string temphex = ss2.str();
        while (difficulty != 0 && hex_greater(temphex, diff)) {
//                triedFillers.push_back(filler);
//                fillerHashes.push_back(sha256(all + to_string(filler)));
            temp = all + to_string(filler);
            ss2 << hex << temp;
            temphex = ss2.str();
            filler++;
        }


        timeFound = time(NULL);
        hash = sha256(all + to_string(filler));

        found = true;
    }


    return hash;
}


long Block::getFiller() {
    return filler;
}

time_t Block::getTimeFound() {
    return timeFound;
}

unsigned long Block::getDifficulty() {
    return difficulty;
}

void Block::setDifficulty(unsigned long diff) {
    found = false;
    this->difficulty = diff;
}

void Block::setPreviousHash(string prevHash) {
    found = false;
    this->previousHash = prevHash;
}

string Block::getPreviousHash() {
    return previousHash;
}

void Block::addTransaction(Transaction transaction) {
    found = false;
    this->transactions.push_back(transaction);
}

void Block::removeTransaction(int position) {
    cout << "Not implemented yet \n";
}

vector<Transaction> Block::getTransactions() {
    vector<Transaction> vecOfStr(transactions.begin(), transactions.end());
    return vecOfStr;
}

string Block::forceFindNewHash() {
    found = false;
    return getHash();
}

