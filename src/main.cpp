#include "app_info.h"
#include "image_loader.h"
#include<iostream>
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: p1_app <image_path>" << std::endl;
        return 1;
    }
    printAppInfo(1);
    std::string imagePath = argv[1];

    cv::Mat image = loadImage(imagePath);

    if (image.empty())
    {
        std::cerr << "Failed to load image." << std::endl;
        return 1;
    }

    std::cout << "\nImage loaded successfully." << std::endl;
    std::cout << "Width: " << image.cols << std::endl;
    std::cout << "Height: " << image.rows << std::endl;
    std::cout << "Channels: " << image.channels() << std::endl;

    return 0;
}