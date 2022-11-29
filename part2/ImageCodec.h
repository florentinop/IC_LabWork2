//
// Created by diogo on 14/11/22.
//

#ifndef INC_IMAGECODEC_H
#define INC_IMAGECODEC_H

#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include "Golomb.h"
#include "BitStream.h"
#include <opencv4/opencv2/opencv.hpp>
#include <bitset>

using namespace cv;
using namespace std;

class ImageCodec
{
private:
    string path;

public:
    explicit ImageCodec(string path)
    {
        this->path = std::move(path);
    }

    void encode(Mat img)
    {
        vector<Vec3b> res;
        for (int i = 0; i < img.cols; i++){
            res.push_back(Vec3b(0,0,0));
        }
        
        for (size_t row = 1; row < (size_t)img.rows; row++)
        {
            for (size_t col = 0; col < (size_t)img.cols; col++)
            {
                if(col==0){
                    res.push_back(Vec3b(0,0,0));
                    continue;
                }
                
                Vec3b a, b, c, x;
                a = img.at<Vec3b>(row, col - 1);
                b = img.at<Vec3b>(row - 1, col);
                c = img.at<Vec3b>(row - 1, col - 1);
                for (size_t i = 0; i < 3; i++)
                {
                    short min_ab = min(a[i], b[i]), max_ab = max(a[i], b[i]);
                    if (c[i] >= max_ab)
                        x[i] = min_ab;
                    else if (c[i] <= min_ab)
                        x[i] = max_ab;
                    else
                        x[i] = a[i] + b[i] - c[i];
                }
                res.push_back(x);
            }
        }
    
        Golomb golomb{32};
        BitStream writeStream{path};
        writeStream.writeBits(bitset <16> (img.rows).to_string());
        writeStream.writeBits(bitset <16> (img.cols).to_string());

        for (auto re : res)
        {
            for (size_t i = 0; i < 3; i++)
            {
                writeStream.writeBits(golomb.encode(re[i]));
            }
        }
    }

    void decode(const string &outPath)
    {
        Golomb golomb{32};
        BitStream readStream{path};
        int rows = stoi(readStream.readBits(16), nullptr, 2);
        int cols = stoi(readStream.readBits(16), nullptr, 2);
        Mat img(rows, cols, IMREAD_COLOR);
       
        string decoding;
        unsigned int lengthToRead = 1024;
        int idx = 0;
        decoding = readStream.readBits(lengthToRead);
        vector <unsigned char>res; 

        

        while (decoding.size() >= lengthToRead) {
            string bitsToDecode = decoding;
            while (bitsToDecode.size() > lengthToRead) {
                res.push_back((unsigned char) golomb.decode(bitsToDecode, idx));
                bitsToDecode = bitsToDecode.substr(idx, bitsToDecode.size());
            }
            decoding = bitsToDecode;
            decoding += readStream.readBits(lengthToRead);
        }

        
        
        while (idx > 0) {
            res.push_back((unsigned char) golomb.decode(decoding, idx));
            decoding = decoding.substr(idx, decoding.size());
        }
        
        int c=0;
        int r=0;
        for (size_t i = 0; i < res.size(); i+=3){
            if(c == img.cols)
                c=0,r++;
            img.at<Vec3b>(r, c++) = Vec3b(res[i],res[i+1],res[i+2]);
        }
       
        imwrite(outPath, img);
    }
};

#endif
