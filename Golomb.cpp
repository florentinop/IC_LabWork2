//
// Created by diogo on 07/11/22.
//

#include "Golomb.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: golomb <m> <n>";
        return 1;
    }
    Golomb golomb {atoi(argv[argc-2])};
    cout << golomb.encode(atoi(argv[argc-1])) << endl;
    return 0;
}
