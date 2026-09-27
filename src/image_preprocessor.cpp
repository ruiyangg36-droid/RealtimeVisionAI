#include "image_preprocessor.h"
#include<algorithm>
#include<cmath>
#include<opencv2/imgproc.hpp>
#include <stdexcept>
cv::Mat preprocessImage(
    const cv::Mat& image,
    int resizeShortSide,
    int cropSize
)
{
    // 参数合法性检查
    if (image.empty())
    {
        throw std::runtime_error("Input image is empty.");
    }
    if (resizeShortSide <= 0 || cropSize <= 0)
    {
        throw std::runtime_error(
            "resizeShortSide and cropSize must be positive."
        );
    }

    // 保持宽高比 resize，短边缩放到 resizeShortSide
    int newWidth;
    int newHeight;

    if (image.cols < image.rows)
    {
        newWidth = resizeShortSide;
        newHeight = static_cast<int>(
            std::round(
                static_cast<double>(image.rows)
                * resizeShortSide
                / image.cols
            )
        );
    }
    else
    {
        newHeight = resizeShortSide;
        newWidth = static_cast<int>(
            std::round(
                static_cast<double>(image.cols)
                * resizeShortSide
                / image.rows
            )
        );
    }

    // 执行 resize
    cv::Mat resized;
    cv::resize(
        image,
        resized,
        cv::Size(newWidth, newHeight),
        0,
        0,
        cv::INTER_LINEAR
    );

    // Center Crop，从中心裁剪 cropSize × cropSize
    if (cropSize > resized.cols || cropSize > resized.rows)
    {
        throw std::runtime_error(
            "cropSize is larger than resized image."
        );
    }

    int cropX = (resized.cols - cropSize) / 2;
    int cropY = (resized.rows - cropSize) / 2;
    cv::Rect roi(cropX, cropY, cropSize, cropSize);
    cv::Mat cropped = resized(roi);

    // BGR -> RGB
    cv::Mat rgbImage;
    cv::cvtColor(
        cropped,
        rgbImage,
        cv::COLOR_BGR2RGB
    );

    // uint8 -> float32，并缩放到 [0,1]
    cv::Mat floatImage;
    rgbImage.convertTo(
        floatImage,
        CV_32F,
        1.0 / 255.0
    );

    // ImageNet mean/std 标准化,把数据变换成“均值为 0、标准差为 1”的分布。
	//ResNet18 训练时用了这组均值和标准差，推理时必须用同样的值，
	// 否则模型看到的输入和训练时不一致，精度会下降。
    const cv::Vec3f mean(0.485f, 0.456f, 0.406f);
    const cv::Vec3f std(0.229f, 0.224f, 0.225f);

    for (int row = 0; row < floatImage.rows; ++row)
    {
        for (int col = 0; col < floatImage.cols; ++col)
        {
            // 必须用引用，否则修改的是副本
            cv::Vec3f& pixel = floatImage.at<cv::Vec3f>(row, col);
            pixel[0] = (pixel[0] - mean[0]) / std[0];
            pixel[1] = (pixel[1] - mean[1]) / std[1];
            pixel[2] = (pixel[2] - mean[2]) / std[2];
        }
    }

    // 返回标准化后的 float32 图像
    return floatImage;
}
std::vector<float> convertHWCToCHW(const cv::Mat& image)
{
    int H = image.rows;
    int W = image.cols;
    int C = image.channels();

    std::vector<float> chwData(C * H * W);

    for (int h = 0; h < H; ++h)
    {
        for (int w = 0; w < W; ++w)
        {
            cv::Vec3f pixel = image.at<cv::Vec3f>(h, w);

            for (int c = 0; c < C; ++c)
            {
                chwData[c * H * W + h * W + w] = pixel[c];
            }
        }
    }

    return chwData;
}
