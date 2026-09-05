#pragma once
#include<opencv2/core.hpp>
#include<vector>
cv::Mat preprocessImage(
	const cv::Mat& image,
	int targetWidth,
	int targetHeight
);
std::vector<float> convertHWCToCHW(
	const cv::Mat& image
);
