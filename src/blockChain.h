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
    unsigned long difficulty = 9999999999999999;
//    int hashrate = 1000;
    int targetTime = 10; //in seconds
    Block currentHashedBlock;
    bool blockHashed = true;
    bool ready = true;
    string projectName;
    string projectNameHash;

    void setDifficulty();

    void hashCurrentBlock();

public:
    BlockChain() {
    }

    void setTargetTime(int target);

    int getTargetTime();

    unsigned long getDifficulty();

    Block getCurrentBlockHashed();

    bool getBlockhashed();

    void pushBlock();

    void addBlock(Block newBlock);

    void removeBlock();

    bool verifyChain(int start = 0, int end = -1);


//    void setProjectName(string projectName);
//
//    string getProjectNameHash();

    vector<Block> getBlocks();
};

#endif //GRAPHENECHAIN_BLOCK_H
