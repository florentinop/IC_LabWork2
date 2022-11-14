//
// Created by diogo on 14/11/22.
//

#include "LosslessAudioCodec.h"
#include "Golomb.h"

#include <iostream>
#include <vector>
#include <sndfile.hh>
#include <algorithm>
#include <cmath>

constexpr size_t FRAMES_BUFFER_SIZE = 65536; // Buffer for reading frames

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 3) {
        cerr << "Usage: " << argv[0] << " <input file> <Golomb parameter (m)>\n";
        return 1;
    }

    SndfileHandle sndFile { argv[1] };
    if(sndFile.error()) {
        cerr << "Error: invalid input file\n";
        return 1;
    }

    if((sndFile.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
        cerr << "Error: file is not in WAV format\n";
        return 1;
    }

    if((sndFile.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
        cerr << "Error: file is not in PCM_16 format\n";
        return 1;
    }

    size_t nFrames;
    vector<short> samples(FRAMES_BUFFER_SIZE * sndFile.channels());

    vector<short> temp(samples.size());

    while((nFrames = sndFile.readf(samples.data(), FRAMES_BUFFER_SIZE))) {
        samples.resize(nFrames * sndFile.channels());
        temp.insert(temp.end(), samples.begin(), samples.end());
    }

    LosslessAudioCodec codec { temp, sndFile.channels()};
    vector<int> residuals = codec.calculateResiduals();
    int max = *max_element(residuals.begin(), residuals.end());
    int m = (int) (max / log2(max));
    Golomb golomb {m};
    string golombCoding;
    for (auto res: residuals) {
        golombCoding += golomb.encode(res);
    }
    cout << residuals[1] << endl;
    cout << "Encoding: " << golomb.encode(residuals[1]) << endl;
    cout << "Decoding: " << golomb.decode(golomb.encode(residuals[1])) << endl;
    return 0;
}