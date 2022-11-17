//
// Created by diogo on 01/11/22.
//

#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: negative <image> <negative image>\n";
        return 1;
    }

    std::string image = std::string(argv[1]);
    std::string path = std::string(argv[2]);

    Mat img = imread(image, IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cout << "Could not read the image: " << image << std::endl;
        return 1;
    }

    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            img.at<uchar>(y, x) = 255 - img.at<uchar>(y, x);
        }
    }

    imwrite(path, img);

    return 0;
}
