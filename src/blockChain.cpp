#include "blockChain.h"
#include <iostream>
#include <string>
#include <vector>
#include "block.h"
#include "transaction.h"
#include <algorithm>
#include <ctime>
#include <fstream>

using namespace std;

BlockChain::BlockChain() {
    projectName = "";
    projectNameHash = sha256(projectName);
}



void BlockChain::setDifficulty(unsigned long long diff) {
    difficulty = diff;
}

void BlockChain::hashCurrentBlock() {
    if (!blockHashed && !ready) {
        currentHashedBlock.getHash();                       //this line might be the problem
        blockHashed = true;
    }
}

void BlockChain::setTargetTime(int target) {
    targetTime = target;
}

int BlockChain::getTargetTime() {
    return targetTime;
}

unsigned long long BlockChain::getDifficulty() {
    return difficulty;
}

Block BlockChain::getCurrentBlockHashed() {
    return currentHashedBlock;
}

bool BlockChain::getBlockhashed() {
    return blockHashed;
}

void BlockChain::pushBlock() {
    if (blockHashed && !ready) {
        time_t latest = currentHashedBlock.getTimeFound();
        double timeDifference;
        if (chain.size() != 0) {
            time_t previous = chain.back().getTimeFound();

             timeDifference = difftime(latest, previous); //in seconds
        } else {
            timeDifference = 10;
        }
        chain.push_back(currentHashedBlock);

//        setDifficulty();
//if (timeDifference < 0.1) timeDifference = 0.1;
//        cout << timeDifference << "\n";
//        if (targetTime > timeDifference)
//            setDifficulty(getDifficulty()-(adjustmentFactor*((targetTime/timeDifference))));
//        if (targetTime < timeDifference)
//            setDifficulty(getDifficulty()+(adjustmentFactor*((timeDifference/targetTime))));
//        while (getDifficulty() > 10) {
//            numZerosAtStart--;
//            if (numZerosAtStart < 0) {
//                numZerosAtStart = 0;
//            } else {
//                setDifficulty(getDifficulty()/10);
//            }
//        }
//        while (getDifficulty() < 1) {
//            numZerosAtStart++;
//            setDifficulty(getDifficulty()+10);
//
//        }
//        cout << getDifficulty();


        addToFile(currentHashedBlock);


        ready = true;
    }
}

void BlockChain::addBlock(Block newBlock) {
    blockHashed = false;
    ready = false;
    currentHashedBlock = newBlock;
//    cout << "set success\n";
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

//void BlockChain::setProjectNameHash(string projectName, string projectNameHash) {
//    this->projectName = "GrapheneChain"; //Change this to your cryptos name
//    this->projectNameHash = sha256(projectName);
//}
//
//void BlockChain::setProjectNameHash(string projectNameHash) {
//    this->projectNameHash = projectNameHash;
//}
//
//string BlockChain::getProjectNameHash() {
//    return projectNameHash;
//}

vector<Block> BlockChain::getBlocks() {
    vector<Block> vecOfStr(chain.begin(), chain.end());
    return vecOfStr;
}

int BlockChain::getDiffPadding() {
    return numZerosAtStart;
}

void BlockChain::addToFile(Block currentlyHashedBlock) {

}

void BlockChain::resetLocalGetFromFile(string name) {
    resetMem();
}

void BlockChain::resetChain() {

}

void BlockChain::resetMem() {

}

void BlockChain::printFile() {
    string currentText;
    ifstream readFile("out/chain/"+getProjectNameHash()+".txt");
    while (getline (readFile, currentText)) {
        // Output the text from the file
        cout << currentText;
    }
    readFile.close();
}

void BlockChain::setProjectName(string newProjectName) {
    this->projectName = newProjectName;
    projectNameHash = sha256(newProjectName);
}

string BlockChain::getProjectName() {
    return projectName;
}

string BlockChain::getProjectNameHash() {
    return projectNameHash;
}

