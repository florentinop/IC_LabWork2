//
// Created by diogo on 07/11/22.
//

#ifndef IC_GOLOMB_H
#define IC_GOLOMB_H

#include <string>
#include <cmath>
#include <bitset>

using namespace std;

class Golomb {
private:
    int m;

public:
    Golomb(int m) {
        if (m > 0) {
            this->m = m;
        }
    }

    string encode(int n) {
        int q = n / m;
        int r = n % m;
        string unaryCode = "";
        for (int i = 0; i < q; i++) {
            unaryCode += '0';
        }
        unaryCode += '1';
        string binaryCode = "";
        int logm = (int) log2(m);
        if (r >= pow(2, logm + 1) - m) {
            binaryCode += bitset<32>(r + pow(2, logm + 1) - m).to_string();
            binaryCode = binaryCode.substr(binaryCode.size() - logm - 1, binaryCode.size());
        } else {
            binaryCode += bitset<32>(r).to_string();
            binaryCode = binaryCode.substr(binaryCode.size() - logm, binaryCode.size());
        }
        return unaryCode + binaryCode;
    }

    int decode(string s) {
        return 0;
    }
};


#endif //IC_GOLOMB_H
