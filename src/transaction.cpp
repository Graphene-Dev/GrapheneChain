#include "transaction.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include <ctime>
#include <sstream>
#include <algorithm>
#include "sha256.h"

using namespace std;

//Constructor, initialize default values
Transaction::Transaction(string from, string to, int amount) {
    sender = from;
    receiver = to;
    this->amount = amount;
    current_time = time(NULL);
}

//accessor of the amount in the transaction
int Transaction::getAmount() {
    return amount;
}

//modifier for the amount in the transaction
void Transaction::setAmount(int amount) {
    this->amount = amount;
    current_time = time(NULL);
}

//accessor for the sender of the transaction
string Transaction::getSender() {
    return sender;
}

//modifier for the sender of the transaction
void Transaction::setSender(string from) {
    sender = from;
    current_time = time(NULL);
}

//accessor for the reciever of the transaction
string Transaction::getReceiver() {
    return receiver;
}

//modifier of the reciever of the transaction
void Transaction::setReceiver(string to) {
    receiver = to;
    current_time = time(NULL);
}

//get the transaction in a string
string Transaction::getTransaction() {
    return "From: " + sender + ", To: " + receiver + ", Amount: " + to_string(amount) + ", " +
           to_string(current_time);
}

//return the hash of the transaction
string Transaction::getHash() {
    return sha256(sender + receiver + to_string(amount) + to_string(current_time));
}

string Transaction::toString() {
    string output = "Transaction:";
    output += "\n Date created: ";
    output += current_time;
    
    return "";
}

ostream& operator<<(ostream& out, Transaction& t) {
    return out << t.toString();
}