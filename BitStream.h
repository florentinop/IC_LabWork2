//
// Created by diogo on 11/10/22.
//

#ifndef SNDFILE_EXAMPLE_BITSTREAM_H
#define SNDFILE_EXAMPLE_BITSTREAM_H

#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class BitStream {
private:
    string path;
    unsigned int bitPointer;
    vector<char> buffer;

public:
    BitStream(string path, unsigned int bitPointer) {
        this->path = path;
        this->bitPointer = bitPointer;
    }

    BitStream(string path) : BitStream(path, 0) {}

    char readBit() {
        char res = -1;
        ifstream infile;
        infile.open(path);
        infile.seekg(bitPointer>>3); // bitPointer/8
        if (infile >> res) {
            res >>= 7 - (bitPointer % 8);
            res &= 1;
            bitPointer++;
            res = (res == 0 ? '0' : '1');
        }
        infile.close();
        return res;
    }

    string readBits(unsigned int n) {
        string res;
        ifstream infile;
        infile.open(path);
        for (unsigned int i = 0; i < n; i++) {
            infile.seekg(bitPointer>>3); // bitPointer/8
            char c = -1;
            if (infile >> c) {
                c >>= 7 - (bitPointer % 8);
                c &= 1;
                bitPointer++;
                res += (c == 0 ? '0' : '1');
            }
        }
        return res;
    }

    void writeBit(char bit) {
        buffer.push_back(bit & 1);
        if (buffer.size() >= 8) {
            char res = 0;
            for (unsigned int i = 0; i < 8; i++) {
                res <<= 1;
                res += buffer[i];
            }
            buffer.clear();
            ofstream outfile;
            outfile.open(path, ios::out | ios::app);
            outfile << res;
            outfile.close();
        }
    }

    void writeBits(string bits) {
        ofstream outfile;
        outfile.open(path, ios::out | ios::app);
        for (auto bit: bits) {
            buffer.push_back(bit & 1);
            if (buffer.size() >= 8) {
                char res = 0;
                for (unsigned int i = 0; i < 8; i++) {
                    res <<= 1;
                    res += buffer[i];
                }
                buffer.clear();
                outfile << res;
            }
        }
        outfile.close();
    }

    void setReadPointer(unsigned int bit) {
        bitPointer = bit;
    }
};


#endif //SNDFILE_EXAMPLE_BITSTREAM_H
