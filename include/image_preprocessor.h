#pragma once
#include<opencv2/core.hpp>
#include<vector>
cv::Mat preprocessImage(
	const cv::Mat& image,
	int resizeShortSide,
	int cropSize
);
std::vector<float> convertHWCToCHW(
	const cv::Mat& image
);
