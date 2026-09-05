#include "app_info.h"
#include "image_loader.h"
#include<iostream>
#include<image_preprocessor.h>
#include<vector>
int main(int argc, char* argv[])
{
    //判断命令行输入是否正确
    if (argc < 2)
    {
        std::cout << "Usage: p1_app <image_path>" << std::endl;
        return 1;
    }
    printAppInfo(1);
    //判断图片是否真正输入
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
    //修改成目标尺寸->BGR转换成RGB->像素值转成浮点型->像素值缩小
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
    std::cout << "Float32: " << (processedImage.depth() == CV_32F?"yes" : "no") << '\n';
    cv::Vec3f pixel = processedImage.at<cv::Vec3f>(0, 0);
    std::cout << "\nPixel(0,0): " << pixel[0] << " " << pixel[1] << " " << pixel[2] << '\n';
    //把图片默认的HWC（高度，宽度，通道数）转换成CHW 并验证
    std::vector<float> inputData = convertHWCToCHW(processedImage);
    int H = processedImage.rows;
    int W = processedImage.cols;
    std::cout << "CHW data size: " << inputData.size() << "\n";
    cv::Vec3f firstPixel = processedImage.at<cv::Vec3f>(0, 0);
    std::cout << "HWC Pixel(0,0): R = " << firstPixel[0] 
        << ", G = " << firstPixel[1] << ", B = " << firstPixel[2] << "\n";
    std::cout << "CHW first R: " << inputData[0] << "\n";
    std::cout << "CHW first G: " << inputData[H * W] << "\n";
    std::cout << "CHW first B: " << inputData[2 * H * W] << "\n";
    return 0;
}