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
    int m = 0;

public:
    Golomb(int m) {
        if (m > 0) {
            this->m = m;
        }
    }

    string encode(int n) {
        int q = abs(n) / m;
        int r = abs(n) % m;
        string unaryCode;
        for (int i = 0; i < q; i++) {
            unaryCode += '0';
        }
        unaryCode += '1';
        string binaryCode;
        int b = (int) log2(m) + 1;
        if (r < pow(2, b) - m) {
            binaryCode += bitset<32>(r).to_string();
            binaryCode = binaryCode.substr(binaryCode.size() - b + 1, binaryCode.size());
        } else {
            binaryCode += bitset<32>(r + (int) pow(2, b) - m).to_string();
            binaryCode = binaryCode.substr(binaryCode.size() - b, binaryCode.size());
        }
        if (n == 0) {
            return unaryCode + binaryCode;
        }
        return unaryCode + binaryCode + (n > 0 ? '0' : '1');
    }

    int decode(const string& s, int& sLength) {
        int q = 0;
        for (auto &c: s) {
            if (c == '0') {
                q += 1;
            } else {
                break;
            }
        }
        sLength = q + 1;
        int b = (int) log2(m);
        if ((unsigned long) q + 1 >= s.size()) {
            sLength = 0;
            return q * m;
        }
        string bBits = s.substr(q + 1, b);
        int rPrime = stoi(bBits, nullptr, 2);
        int r = 0;
        string signBit;
        if (rPrime < pow(2, b + 1) - m) {
            r = rPrime;
            sLength += b;
            int value = q * m + r;
            if (value == 0) {
                return value;
            }
            if ((unsigned int) q + b + 1 >= s.size()) {
                sLength = 0;
                return q * m + r;
            }
            signBit = s.substr(q + b + 1, 1);
            sLength++;
            return value * (signBit == "0" ? 1 : -1);
        } else {
            string bBitsPlusOne = s.substr(q + 1, b + 1);
            rPrime = stoi(bBitsPlusOne, nullptr, 2);
            r = rPrime - (int) pow(2, b + 1) + m;
            sLength += b + 1;
            if ((unsigned long) q + b + 2 >= s.size()) {
                sLength = 0;
                return q * m + r;
            }
            signBit = s.substr(q + b + 2, 1);
            sLength++;
            int value = q * m + r;
            return value * (signBit == "0" ? 1 : -1);
        }
    }
};

#endif //IC_GOLOMB_H
