#include "ImageProcessor.hpp"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>

cv::Mat ImageProcessor::loadImage(const char* imagePath)
{
    std::ifstream file(imagePath, std::ios::binary);

    if (!file)
    {
        std::cerr << "Cannot open image file: "
                  << imagePath << std::endl;

        return cv::Mat();
    }

    std::vector<unsigned char> buffer(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    cv::Mat image = cv::imdecode(
        buffer,
        cv::IMREAD_COLOR
    );

    if (image.empty())
    {
        std::cerr << "Failed to decode image: "
                  << imagePath << std::endl;

        return cv::Mat();
    }

    std::cout << "Image loaded successfully: "
              << imagePath
              << " | width=" << image.cols
              << " height=" << image.rows
              << std::endl;

    return image;
}