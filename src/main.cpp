#include "app_info.h"
#include "image_loader.h"
#include "image_preprocessor.h"
#include <iostream>
#include <vector>
int main(int argc, char* argv[])
{
    // 判断命令行输入是否正确
    if (argc < 2)
    {
        std::cout << "Usage: p1_app <image_path>" << std::endl;
        return 1;
    }
    printAppInfo(1);
    // 获取图片路径
    std::string imagePath = argv[1];
    cv::Mat image = loadImage(imagePath);
    // 判断图片是否真正加载成功
    if (image.empty())
    {
        std::cerr << "Failed to load image." << std::endl;
        return 1;
    }
    std::cout << "\nImage loaded successfully." << std::endl;
    std::cout << "\nOriginal:\n";
    std::cout << "Width: " << image.cols << '\n';
    std::cout << "Height: " << image.rows << '\n';
    std::cout << "Channels: " << image.channels() << '\n';

    // ResNet18 预处理参数
    const int resizeShortSide = 256;
    const int cropSize = 224;

    // 保持宽高比 resize
    // -> Center Crop
    // -> BGR 转 RGB
    // -> 转为 Float32
    // -> 缩放到 [0,1]
    // -> mean/std 标准化
    cv::Mat processedImage = preprocessImage(
        image,
        resizeShortSide,
        cropSize
    );

    // 验证预处理后的图像信息
    std::cout << "\nPreprocessed:\n";
    std::cout << "Width: " << processedImage.cols << '\n';
    std::cout << "Height: " << processedImage.rows << '\n';
    std::cout << "Channels: " << processedImage.channels() << '\n';
    std::cout << "Float32: "
              << (processedImage.depth() == CV_32F ? "yes" : "no")
              << '\n';

    // mean/std 标准化后像素值不再限制在 [0,1]
    cv::Vec3f pixel = processedImage.at<cv::Vec3f>(0, 0);

    std::cout << "\nNormalized Pixel(0,0):\n";
    std::cout << "R = " << pixel[0] << '\n';
    std::cout << "G = " << pixel[1] << '\n';
    std::cout << "B = " << pixel[2] << '\n';

    // HWC -> CHW
    std::vector<float> inputData =
        convertHWCToCHW(processedImage);

    int H = processedImage.rows;
    int W = processedImage.cols;

    std::cout << "\nCHW data size: "
              << inputData.size()
              << '\n';

    // 验证 HWC -> CHW 转换是否正确
    cv::Vec3f firstPixel =
        processedImage.at<cv::Vec3f>(0, 0);

    std::cout << "\nHWC Pixel(0,0): "
              << "R = " << firstPixel[0]
              << ", G = " << firstPixel[1]
              << ", B = " << firstPixel[2]
              << '\n';

    std::cout << "CHW first R: "
              << inputData[0] << '\n';

    std::cout << "CHW first G: "
              << inputData[H * W] << '\n';

    std::cout << "CHW first B: "
              << inputData[2 * H * W] << '\n';

    return 0;
}