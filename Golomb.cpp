//
// Created by diogo on 07/11/22.
//

#include "Golomb.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: golomb [-e] <m> <n>" << endl;
        cerr << "or     golomb -d <m> <s>" << endl;
        return 1;
    }

    bool encode = true;

    if (argc == 4) {
        if (string(argv[1]) == "-d") {
            encode = false;
        }
    }

    Golomb golomb {atoi(argv[argc-2])};

    if (encode) {
        cout << golomb.encode(atoi(argv[argc-1])) << endl;
    } else {
        cout << golomb.decode(string(argv[argc-1])) << endl;
    }

    return 0;
}
