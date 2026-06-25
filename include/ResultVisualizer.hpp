#pragma once

#include <opencv2/opencv.hpp>
#include "DetectionResult.hpp"

class ResultVisualizer
{
public:
    static void saveAnnotatedImage(
        const cv::Mat& image,
        const DetectionResult& result,
        const char* outputPath
    );
};