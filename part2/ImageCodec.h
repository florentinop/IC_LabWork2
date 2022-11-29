//
// Created by diogo on 14/11/22.
//

#ifndef INC_IMAGECODEC_H
#define INC_IMAGECODEC_H

#include "Golomb.h"
#include "BitStream.h"

#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <opencv4/opencv2/opencv.hpp>
#include <bitset>

using namespace cv;
using namespace std;

class ImageCodec {
private:
    string path;

public:
    explicit ImageCodec(string path) {
        this->path = std::move(path);
    }

    void encode(Mat img) {
        vector<Vec3b> res;
        // First pixel in raster-scan order
        Vec3b predictor(0, 0, 0);
        Vec3b pixel = img.at<Vec3b>(0, 0);
        Vec3b residual(pixel[0] - predictor[0], pixel[1] - predictor[1], pixel[2] - predictor[2]);
        res.emplace_back(residual);
        // First row
        for (int i = 1; i < img.cols; i++) {
            predictor = img.at<Vec3b>(0, i - 1);
            pixel = img.at<Vec3b>(0, i);
            residual = Vec3b(pixel[0] - predictor[0], pixel[1] - predictor[1], pixel[2] - predictor[2]);
            res.emplace_back(residual);
        }
        for (int row = 1; row < img.rows; row++) {
            for (int col = 0; col < img.cols; col++) {
                if (col == 0) {  // First column
                    predictor = img.at<Vec3b>(row - 1, col);
                } else {
                    Vec3b a, b, c;
                    a = img.at<Vec3b>(row, col - 1);
                    b = img.at<Vec3b>(row - 1, col);
                    c = img.at<Vec3b>(row - 1, col - 1);
                    for (int i = 0; i < 3; i++) {
                        short min_ab = min(a[i], b[i]), max_ab = max(a[i], b[i]);
                        if (c[i] >= max_ab)
                            predictor[i] = min_ab;
                        else if (c[i] <= min_ab)
                            predictor[i] = max_ab;
                        else
                            predictor[i] = a[i] + b[i] - c[i];
                    }
                }
                pixel = img.at<Vec3b>(row, col);
                residual = Vec3b(pixel[0] - predictor[0], pixel[1] - predictor[1], pixel[2] - predictor[2]);
                res.emplace_back(residual);
            }
        }
        Golomb golomb{32};
        BitStream writeStream{path};
        writeStream.writeBits(bitset<16>(img.rows).to_string());
        writeStream.writeBits(bitset<16>(img.cols).to_string());
        for (auto re : res) {
            for (int i = 0; i < 3; i++) {
                writeStream.writeBits(golomb.encode(re[i]));
            }
        }
    }

    vector<unsigned char> decode(const string &outPath) {
        Golomb golomb{32};
        BitStream readStream{path};
        int rows = stoi(readStream.readBits(16), nullptr, 2);
        int cols = stoi(readStream.readBits(16), nullptr, 2);
        string decoding;
        unsigned int const BLOCK_SIZE = 1024;
        int idx = 0;
        vector<unsigned char> res;
        decoding = readStream.readBits(BLOCK_SIZE);
        while (decoding.size() >= BLOCK_SIZE) {
            string bitsToDecode = decoding;
            while (bitsToDecode.size() > BLOCK_SIZE) {
                res.push_back((unsigned char) golomb.decode(bitsToDecode, idx));
                bitsToDecode = bitsToDecode.substr(idx, bitsToDecode.size());
            }
            decoding = bitsToDecode;
            decoding += readStream.readBits(BLOCK_SIZE);
        }
        while (idx < (int) decoding.size()) {
            res.push_back((unsigned char) golomb.decode(decoding, idx));
            decoding = decoding.substr(idx, decoding.size());
        }
        res.push_back((unsigned char) golomb.decode(decoding, idx));
        // Make res a multiple of 3 if not already
        for (size_t i = 0; i < res.size() % 3; i++) {
            res.pop_back();
        }
        Mat img = Mat::zeros(rows, cols, CV_8UC3);
        // First pixel
        img.at<Vec3b>(0, 0) = Vec3b(res[0], res[1], res[2]);
        int colIdx = 3 * cols;
        // First row
        for (int i = 3; i < colIdx; i += 3) {
            res[i] = res[i] + res[i - 3];
            res[i + 1] = res[i + 1] + res[i - 2];
            res[i + 2] = res[i + 2] + res[i - 1];
            img.at<Vec3b>(0, i / 3) = Vec3b(res[i], res[i + 1], res[i + 2]);
        }
        unsigned char a, b, c, min_ab, max_ab;
        for (int i = colIdx; i < (int) res.size(); i += 3) {
            if (i % colIdx == 0) {  // First column
                res[i] = res[i] + res[i - colIdx];
                res[i + 1] = res[i + 1] + res[i + 1 - colIdx];
                res[i + 2] = res[i + 2] + res[i + 2 - colIdx];
            } else {
                for (int j = 0; j < 3; j++) {
                    a = res[i + j - 3];
                    b = res[i + j - colIdx];
                    c = res[i + j - 3 - colIdx];
                    min_ab = min(a, b);
                    max_ab = max(a, b);
                    if (c >= max_ab) {
                        res[i + j] = res[i + j] + min_ab;
                    } else if (c <= min_ab) {
                        res[i + j] = res[i + j] + max_ab;
                    } else {
                        res[i + j] = res[i + j] + a + b - c;
                    }
                }
            }
            img.at<Vec3b>(i / colIdx, (i % colIdx) / 3) = Vec3b(res[i], res[i + 1], res[i + 2]);
        }
        imwrite(outPath, img);
        return res;
    }
};

#endif
