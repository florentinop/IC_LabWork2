//
// Created by diogo on 01/11/22.
//

#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char* argv[]) {
    int rotateConstants[] {ROTATE_90_CLOCKWISE, ROTATE_180, ROTATE_90_COUNTERCLOCKWISE};
    int rotateIndex = -1;

    if (argc < 3) {
        std::cerr << "Usage: rotate [value] <image> <rotated image>\n";
        std::cerr << "              (value in {0, 90, 180, 270}, default 0)\n";
        return 1;
    }

    if (argc == 4) {
        switch(atoi(argv[1])) {
            case 90:
                rotateIndex = 0;
                break;
            case 180:
                rotateIndex = 1;
                break;
            case 270:
                rotateIndex = 2;
                break;
            default:
                rotateIndex = -1;
                break;
        }
    }

    std::string image = std::string(argv[argc-2]);
    std::string path = std::string(argv[argc-1]);

    Mat img = imread(image, IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "Could not read the image: " << image << std::endl;
        return 1;
    }

    if (rotateIndex != -1) {
        rotate(img, img, rotateConstants[rotateIndex]);
    }

    imwrite(path, img);

    return 0;
}
