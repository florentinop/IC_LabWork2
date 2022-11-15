//
// Created by diogo on 14/11/22.
//

#ifndef INC_02_AUDIOCODEC_H
#define INC_02_AUDIOCODEC_H

#include <utility>
#include <vector>

using namespace std;

class AudioCodec {
private:
    vector<short> samples;
    int channels;

public:
    AudioCodec(vector<short> samples, int channels) {
        this->samples = std::move(samples);
        this->channels = channels;
    }

    vector<int> calculateResiduals() {
        vector<int> res(2 * samples.size(), 0);
        if (channels == 1) {
            int posIdx = 0;
            int negIdx = 1;
            for (unsigned int i = 1; i < samples.size(); i++) {
                int residual = samples[i] - samples[i-1];
                if (residual >= 0) {
                    res[posIdx] = residual;
                    posIdx += 2;
                } else {
                    res[negIdx] = -residual;
                    negIdx += 2;
                }
            }
        } else {
            int posIdxCh1 = 0;
            int negIdxCh1 = 2;
            int posIdxCh2 = 1;
            int negIdxCh2 = 3;
            // Channel 1
            int residual = samples[1] / 2;
            if (residual >= 0) {
                res[0] = residual;
                posIdxCh1 += 4;
            } else {
                res[2] = -residual;
                negIdxCh1 += 4;
            }
            // Channel 2
            residual = samples[0] / 2;
            if (residual >= 0) {
                res[1] = residual;
                posIdxCh2 += 4;
            } else {
                res[3] = -residual;
                negIdxCh2 += 4;
            }
            for (unsigned int i = 2; i < samples.size(); i++) {
                if ((i % 2) == 0) {
                    residual = (samples[i - 2] + samples[i + 1]) / 2;
                    if (residual >= 0) {
                        res[posIdxCh1] = residual;
                        posIdxCh1 += 4;
                    } else {
                        res[negIdxCh1] = -residual;
                        negIdxCh1 += 4;
                    }
                } else {
                    residual = (samples[i - 2] + samples[i - 1]) / 2;
                    if (residual >= 0) {
                        res[posIdxCh2] = residual;
                        posIdxCh2 += 4;
                    } else {
                        res[negIdxCh2] = -residual;
                        negIdxCh2 += 4;
                    }
                }
            }
        }
        unsigned long endIdx = res.size();
        for (unsigned int i = 0; i < res.size(); i++) {
            if (res[res.size() - 1 - i] != 0) {
                endIdx = i;
                break;
            }
        }
        res.resize(res.size() - endIdx);
        return res;
    }
};


#endif //INC_02_AUDIOCODEC_H
