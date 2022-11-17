//
// Created by diogo on 01/11/22.
//

#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char* argv[]) {
    int beta {0};

    if (argc < 3) {
        std::cerr << "Usage: changeIntensity [beta] <image> <modified image>\n";
        std::cerr << "                       (beta in [-100, 100], default 0: lower = less light, "
                     "higher = more light)\n";
        return 1;
    }

    if (argc == 4) {
        beta = atoi(argv[1]);
        if (beta < -100 || beta > 100) {
            std::cerr << "Invalid value for beta\n";
            return 1;
        }
    }

    std::string image = std::string(argv[argc-2]);
    std::string path = std::string(argv[argc-1]);

    Mat img = imread(image, IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "Could not read the image: " << image << std::endl;
        return 1;
    }

    Mat out = Mat::zeros(img.size(), img.type());

    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            for (int c = 0; c < img.channels(); c++) {
                out.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(img.at<Vec3b>(y, x)[c] + beta);
            }
        }
    }

    imwrite(path, out);

    return 0;
}
