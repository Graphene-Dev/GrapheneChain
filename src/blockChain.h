#ifndef GRAPHENECHAIN_BLOCKCHAIN_H
#define GRAPHENECHAIN_BLOCKCHAIN_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "sha256.h"
#include "block.h"
#include <ctime>
#include <algorithm>

//Block-chain class, contains all of the blocks
class BlockChain {
    list<Block> chain;
//    int length = 0;
    int numZerosAtStart = 3;
    unsigned long long difficulty = 0x1;
//    int hashrate = 1000;
    int targetTime = 10; //in seconds
    Block currentHashedBlock;
    bool blockHashed = false;
    bool ready = true;
    string projectName;
    string projectNameHash;
    int adjustmentFactor = 1;

    void setDifficulty(unsigned long long diff);

    void hashCurrentBlock();


public:
    BlockChain();

    BlockChain(string name);

    void setTargetTime(int target);

    int getTargetTime();

    unsigned long long getDifficulty();

    Block getCurrentBlockHashed();

    bool getBlockhashed();

    void pushBlock();

    void addBlock(Block newBlock);

    void removeBlock();

    bool verifyChain(int start = 0, int end = -1);

    int getDiffPadding();

    void resetChain();

    void setProjectName(string newProjectName);
//
    string getProjectNameHash();

    string getProjectName();

    vector<Block> getBlocks();

    void addToFile(Block currentlyHashedBlock);

    void resetLocalGetFromFile(string name);

    void resetMem();

    void printFile();

    BlockChain readFile();

    void writeToFile();

    string toString();

    string getBlockChain();
};

ostream& operator<<(ostream& out, BlockChain& b);
#endif //GRAPHENECHAIN_BLOCK_H
