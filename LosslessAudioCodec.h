//
// Created by diogo on 14/11/22.
//

#ifndef INC_02_LOSSLESSAUDIOCODEC_H
#define INC_02_LOSSLESSAUDIOCODEC_H

#include <utility>
#include <vector>

using namespace std;

class LosslessAudioCodec {
private:
    vector<short> samples;
    int channels;

public:
    LosslessAudioCodec(vector<short> samples, int channels) {
        this->samples = std::move(samples);
        this->channels = channels;
    }

    vector<int> calculateResiduals() {
        vector<int> res;
        int posIdx = 0;
        int negIdx = 0;
        if (channels == 1) {
            res.resize(2 * samples.size(), 0);
            for (unsigned int i = 1; i < samples.size(); i++) {
                int residual = samples[i] - samples[i-1];
                if (residual >= 0) {
                    res[2 * (posIdx+++1)] = residual;
                } else {
                    res[2 * (negIdx++) + 1] = -residual;
                }
            }
        } else {
            res.resize(samples.size(), 0);
            int residual = samples[1] / 2;
            if (residual >= 0) {
                res[0] = residual;
            } else {
                res[1] = -residual;
            }
            for (unsigned int i = 2; i < samples.size(); i += 2) {
                residual = (samples[i - 2] + samples[i - 1]) / 2;
                if (residual >= 0) {
                    res[2 * (posIdx+++1)] = residual;
                } else {
                    res[2 * (negIdx++) + 1] = -residual;
                }
            }
        }
        return res;
    }
};


#endif //INC_02_LOSSLESSAUDIOCODEC_H
