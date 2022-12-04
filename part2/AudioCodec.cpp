//
// Created by diogo on 14/11/22.
//

#include "AudioCodec.h"

#include <iostream>
#include <vector>
#include <sndfile.hh>

constexpr size_t FRAMES_BUFFER_SIZE = 65536; // Buffer for reading frames

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 3) {
        cerr << "Usage: " << argv[0] << "<-d/--lossless/--lossy> <input file> <output file>\n";
        cerr << "                        Default: -d\n";
        return 1;
    }

    int mode = 0;

    if (string(argv[1]) == "--lossless") {
        mode = 1;
    } else if (string(argv[1]) == "--lossy") {
        mode = 2;
    }

    if (mode == 0) {
        AudioCodec codec{string(argv[argc - 2])};
        codec.decode(string(argv[argc - 1]));
    } else {
        SndfileHandle sndFile{argv[argc-2]};
        if (sndFile.error()) {
            cerr << "Error: invalid input file\n";
            return 1;
        }

        if ((sndFile.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
            cerr << "Error: file is not in WAV format\n";
            return 1;
        }

        if ((sndFile.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
            cerr << "Error: file is not in PCM_16 format\n";
            return 1;
        }

        size_t nFrames;
        vector<short> samples(FRAMES_BUFFER_SIZE * sndFile.channels());

        vector<short> temp;

        while((nFrames = sndFile.readf(samples.data(), FRAMES_BUFFER_SIZE))) {
            samples.resize(nFrames * sndFile.channels());
            temp.insert(temp.end(), samples.begin(), samples.end());
        }

        AudioCodec codec {string(argv[argc-1])};
        if (mode == 1) {
            codec.losslessEncode(temp, sndFile.channels());
        } else {
            codec.lossyEncode(temp, sndFile.channels());
        }
    }

    return 0;
}