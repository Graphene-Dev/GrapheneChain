#include <iostream>
#include "sha256.h"
using namespace std;

int main(int argc, char *argv[]) {
    cout << "Base Start\n";
    //Content
//    Block block1 = new Block("block");

    cout << "Base End\n";

    string input = "this is a test";
    string hash = sha256(input);

    cout << "sha256('"<< input << "'):" << hash <<  endl;
    return 0;
}


class BlockChain {

public:
    int height;


};

class Block {

public:

    string name; //temp

     Block (string name = "") {
        if (name != "") {
            this->name = name;
        } else {
            this->name = "";
        }

    }

};