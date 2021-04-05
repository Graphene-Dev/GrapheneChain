#include <iostream>
using namespace std;

int main() {
    cout << "Base Start\n";
    //Content
    block("block1");

    cout << "Base End\n";
}


class blockChain {

public:
    int height;


};

class block {

public:

    const String name; //temp

    explicit block(const String& name = null) {
        if (name != null) {
            this->name = name;
        } else {
            this->name = "default";
        }

    }

};