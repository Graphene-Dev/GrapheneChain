#include <string>

#ifndef GRAPHENECHAIN_TRANSACTION_H
#define GRAPHENECHAIN_TRANSACTION_H

#endif //GRAPHENECHAIN_TRANSACTION_H
#include "sha256.h"

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
    Transaction(string from = "", string to = "", int amount = -1);

    //accessor of the amount in the transaction
    int getAmount();

    //modifier for the amount in the transaction
    void setAmount(int amount);


    //accessor for the sender of the transaction
    string getSender();

    //modifier for the sender of the transaction
    void setSender(string from);


    //accessor for the reciever of the transaction
    string getReceiver();

    //modifier of the reciever of the transaction
    void setReceiver(string to);


    //get the transaction in a string
    string getTransaction();


    //return the hash of the transaction
    string getHash();
};