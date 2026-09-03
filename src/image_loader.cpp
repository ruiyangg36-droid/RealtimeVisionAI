#include "image_loader.h"

#include <opencv2/imgcodecs.hpp>

cv::Mat loadImage(const std::string& path)
{
    return cv::imread(path);
} 