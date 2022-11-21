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
        vector<int> res(samples.size(), 0);
        if (channels == 1) {
            for (unsigned int i = 1; i < samples.size(); i++) {
                res[i] = samples[i] - samples[i-1];
            }
        } else {
            // Channel 1
            res[0] = samples[1] / 2;
            // Channel 2
            res[1] = samples[0] / 2;
            for (unsigned int i = 2; i < samples.size(); i++) {
                if ((i % 2) == 0) {
                    res[i] = (samples[i - 2] + samples[i + 1]) / 2;
                } else {
                    res[i] = (samples[i - 2] + samples[i - 1]) / 2;
                }
            }
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
        if (m == 0) {
            string s;
            vector<short> res;
            while ((s = readStream.readBits(8)).size() >= 8) {
                res.push_back((short) (stoi(s, nullptr, 2) << 8));
            }
            SndfileHandle outFile {outPath, SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_PCM_16, channels, 44100};
            outFile.write(res.data(), (long) res.size());
        } else {
            Golomb golomb {m};
            string decoding;
            string readBits;
            vector<short> res;
            unsigned int lengthToRead = m + (int) log2(m) + 2;
            int idx = 0;
            while ((readBits = readStream.readBits(lengthToRead)).size() >= lengthToRead) {
                decoding += readBits;
                res.push_back((short) golomb.decode(readBits, idx));
                decoding = readBits.substr(idx, readBits.size() - idx);
            }
            decoding += readBits;
            while (!decoding.empty()) {
                res.push_back((short) golomb.decode(readBits, idx));
                decoding = readBits.substr(idx, readBits.size() - idx);
            }
            if (channels == 1) {
                for (unsigned long i = 1; i < res.size(); i++) {
                    res[i] = res[i] + res[i-1];
                }
            }
            SndfileHandle outFile {outPath, SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_PCM_16, channels, 44100};
            outFile.write(res.data(), (long) res.size());
        }
    }
};


#endif //INC_02_AUDIOCODEC_H
