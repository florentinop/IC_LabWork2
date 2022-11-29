//
// Created by diogo on 14/11/22.
//

#ifndef INC_02_AUDIOCODEC_H
#define INC_02_AUDIOCODEC_H

#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <sndfile.hh>
#include "Golomb.h"
#include "BitStream.h"

using namespace std;

class AudioCodec {
private:
    string path;

public:
    explicit AudioCodec(string path) {
        this->path = std::move(path);
    }

    void losslessEncode(vector<short> samples, int channels) {
        if (samples.empty())
            return;
        vector<short> res(samples.size());
        res[0] = samples[0];
        for (unsigned int i = 1; i < samples.size(); i++) {
            res[i] = samples[i] - samples[i - 1];
        }
        int max = *max_element(res.begin(), res.end());
        int m = (int) (max / log2(max));
        Golomb golomb {m};
        BitStream writeStream {path};
        writeStream.writeBits(channels == 2 ? "1" : "0");
        writeStream.writeBits(bitset<15>(m).to_string());
        for (auto re: res) {
            writeStream.writeBits(golomb.encode(re));
        }
    }

    void lossyEncode(vector<short> samples, int channels) {
        std::vector<short> res(samples.size());
        int delta = 256;
        for (unsigned long i = 0; i < samples.size(); i++) {
            if (samples[i] % delta >= delta / 2) {
                res[i] = delta * (1 + samples[i] / delta);
                res[i] >>= 8;
            } else {
                res[i] = samples[i] - (samples[i] % delta);
                res[i] >>= 8;
            }
        }
        BitStream writeStream {path};
        writeStream.writeBits(channels == 2 ? "1" : "0");
        writeStream.writeBits("000000000000000");
        for (auto re: res) {
            writeStream.writeBits(bitset<8>(re).to_string());
        }
    }

    void decode(const string& outPath) {
        BitStream readStream {path};
        int channels = (readStream.readBit() == '1' ? 2 : 1);
        int m = stoi(readStream.readBits(15), nullptr, 2);
        vector<short> res;
        if (m == 0) {
            // Lossy encoding
            string s;
            while ((s = readStream.readBits(8)).size() >= 8) {
                res.push_back((short) (stoi(s, nullptr, 2) << 8));
            }
            SndfileHandle outFile {outPath, SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_PCM_16, channels, 44100};
            outFile.write(res.data(), (long) res.size());
        } else {
            // Lossless decoding
            Golomb golomb {m};
            string decoding;
            unsigned int lengthToRead = 1024;
            int idx = 0;
            decoding = readStream.readBits(lengthToRead);
            while (decoding.size() >= lengthToRead) {
                string bitsToDecode = decoding;
                while (bitsToDecode.size() > lengthToRead) {
                    res.push_back((short) golomb.decode(bitsToDecode, idx));
                    bitsToDecode = bitsToDecode.substr(idx, bitsToDecode.size());
                }
                decoding = bitsToDecode;
                decoding += readStream.readBits(lengthToRead);
            }
            while (idx > 0) {
                res.push_back((short) golomb.decode(decoding, idx));
                decoding = decoding.substr(idx, decoding.size());
            }
            if (res.size() % 2 != 0) {
                res.pop_back();
            }
            for (unsigned long i = 1; i < res.size(); i++) {
                res[i] = res[i] + res[i - 1];
            }
            SndfileHandle outFile {outPath, SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_PCM_16, channels, 44100};
            outFile.writef(res.data(), (long) res.size() / channels);
        }
    }
};

#endif //INC_02_AUDIOCODEC_H
