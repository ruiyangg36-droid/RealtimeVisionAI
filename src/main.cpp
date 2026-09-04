#include "app_info.h"
#include "image_loader.h"
#include<iostream>
#include<image_preprocessor.h>
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
    std::cout << "\nOriginal:\n";
    std::cout << "Width: " << image.cols << std::endl;
    std::cout << "Height: " << image.rows << std::endl;
    std::cout << "Channels: " << image.channels() << std::endl;

    const int targetWidth = 320;
    const int targetHeight = 192;
    cv::Mat processedImage = preprocessImage(
        image,
        targetWidth,
        targetHeight
    );
    std::cout << "\nPreprocessed:\n";
    std::cout << "Width: " << processedImage.cols<< '\n';
    std::cout << "Height: " << processedImage.rows<< '\n';
    std::cout << "Channels: " << processedImage. channels()<< '\n';
    return 0;
}