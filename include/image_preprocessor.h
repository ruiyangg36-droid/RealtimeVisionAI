#pragma once
#include<opencv2/core.hpp>
cv::Mat preprocessImage(
	const cv::Mat& image,
	int targetWidth,
	int targetHeight
);
