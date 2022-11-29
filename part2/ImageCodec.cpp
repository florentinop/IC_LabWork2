//
// Created by diogo on 14/11/22.
//

#include <iostream>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include "ImageCodec.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 3) {
        cerr << "Usage: " << argv[0] << "<-d/-e <input file> <output file>\n";
        cerr << "                        Default: -d\n";
        return 1;
    }
    int mode = 0;
    if(string(argv[1]) == "-e")
        mode = 1;
    // decodes
    if (mode == 0) {
        ImageCodec codec{string(argv[argc - 2])};
        codec.decode(string(argv[argc - 1]));
    // encodes
    } else {
        Mat img = imread(string(argv[argc - 2]), IMREAD_COLOR);
        if (img.empty()) {
            cout << "Could not read the image: " << argv[argc - 2] << endl;
            return 1;
        }
        ImageCodec codec{string(argv[argc - 1])};
        codec.encode(img);
    }
    return 0;
}
