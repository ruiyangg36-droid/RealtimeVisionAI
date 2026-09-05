#include "image_preprocessor.h"
#include<opencv2/imgproc.hpp>
cv::Mat preprocessImage(
	const cv::Mat& image,//常量引用传递，工程中这样传递可避免不必要的参数对象复制，保证函数不会修改图像
	int targetWidth,
	int targetHeight
) {
	cv::Mat resizedImage;
	cv::resize(
		image,//输入图像
		resizedImage,//输出图像
		cv::Size(targetWidth, targetHeight)//目标尺寸
	);
	cv::Mat rgbImage;
	cv::cvtColor(
		resizedImage,//输入图像
		rgbImage,//输出图像
		cv::COLOR_BGR2RGB//转换方式 BGR变成RGB，深度学习模型常见图像处理流程按RGB
	);
	cv::Mat floatImage;
	rgbImage.convertTo(
		floatImage,
		CV_32F,
		1.0 / 255.0
	);
	//归一化，为后面pytorch打基础
	return floatImage;
}
std::vector<float> convertHWCToCHW(const cv::Mat& image)
{
	int H = image.rows;
	int W = image.cols;
	int C = image.channels();
	std::vector<float> chwData(C * H * W);
	for (int c = 0; c < C; ++c)
	{
		for (int row = 0; row < H; ++row)
		{
			for (int col = 0; col < W; ++col)
			{
				cv::Vec3f pixel =
					image.at<cv::Vec3f>(row, col);

				int index =
					c * H * W
					+ row * W
					+ col;

				chwData[index] = pixel[c];
			}
		}
	}

	return chwData;
}
