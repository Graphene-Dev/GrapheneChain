#include "blockChain.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "sha256.h"
#include "block.h"
#include "transaction.h"
#include <ctime>
#include <sstream>
#include <algorithm>
using namespace std;

void BlockChain::setDifficulty() {
     /*later*/
}

void BlockChain::hashCurrentBlock() {
    if (!blockHashed && !ready) {
        currentHashedBlock.getHash();
        blockHashed = true;
    }
}

void BlockChain::setTargetTime(int target) {
        targetTime = target;
}

int BlockChain::getTargetTime() {
     return targetTime;
}

unsigned long BlockChain::getDifficulty() {
     return difficulty;
}

Block BlockChain::getCurrentBlockHashed() {
     return currentHashedBlock;
}

bool BlockChain::getBlockhashed() {
    return blockHashed;
}

void BlockChain::pushBlock() {
    if (blockHashed) {
            chain.push_back(currentHashedBlock);
            setDifficulty();
            ready = true;
   }
} 

void BlockChain::addBlock(Block newBlock) {
        blockHashed = false;
        ready = false;
        currentHashedBlock = newBlock;
        hashCurrentBlock();
}

void BlockChain::removeBlock() {
     cout << "Not implemented yet \n";
}

bool BlockChain::verifyChain(int start, int end) {
if (end == -1) {
             end = chain.size();
         }
         Block *blocks = new Block[chain.size()];
         int l = 0;
         for (Block const &i: chain) {
             blocks[l++] = i;
         }

        string currentHash = blocks[start].getHash();
        for (int i = start + 1; i < end; i++) {
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

void BlockChain::setProjectNameHash(string projectName, string projectNameHash) {
    this->projectName = "GrapheneChain"; //Change this to your cryptos name
    this->projectNameHash = sha256(projectName);
}

void BlockChain::setProjectNameHash(string projectNameHash) {
    this->projectNameHash = projectNameHash;
}

string BlockChain::getProjectNameHash() {
    return projectNameHash;
}

vector<Block> BlockChain::getBlocks() {
    vector<Block> vecOfStr(chain.begin(), chain.end());
    return vecOfStr;
}
