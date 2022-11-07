//
// Created by diogo on 01/11/22.
//

#include <opencv4/opencv2/opencv.hpp>

#include <iostream>

using namespace cv;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: copy <original image> <copied image>\n";
        return 1;
    }

    std::string image = std::string(argv[argc-2]);
    std::string path = std::string(argv[argc-1]);

    Mat img = imread(image, IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "Could not read the image: " << image << std::endl;
        return 1;
    }

    Mat cpy_img(img.rows,img.cols,img.type());
    
    //Copy img to cpy_img pixel by pixel
    for (size_t r = 0; r < (size_t)img.rows; r++){
        for (size_t c = 0; c < (size_t)img.cols; c++){
            cpy_img.at<Vec3b>(r,c) = img.at<Vec3b>(r,c);
        }
    }

    imwrite(path, cpy_img);

    return 0;
}
