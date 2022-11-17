//
// Created by diogo on 01/11/22.
//

#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char* argv[]) {
    char horizontal {true};

    if (argc < 3) {
        std::cerr << "Usage: mirror -[h/v] <image> <mirrored image>\n";
        std::cerr << "or     mirror --[horizontal/vertical] <image> <path>\n";
        std::cerr << "              (default: h/horizontal)\n";
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-v" || std::string(argv[i]) == "--vertical") {
            horizontal = false;
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

    Mat out;

    if (horizontal) {
        flip(img, out, 0);
    } else {
        flip(img, out, 1);
    }

    imwrite(path, out);

    return 0;
}
