#pragma once

#include <opencv2/opencv.hpp>

class ImageProcessor
{
public:
    static cv::Mat loadImage(const char* imagePath);
};