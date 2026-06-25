#include "ResultVisualizer.hpp"

#include <opencv2/opencv.hpp>
#include <string>

void ResultVisualizer::saveAnnotatedImage(
    const cv::Mat& image,
    const DetectionResult& result,
    const char* outputPath
)
{
    if (image.empty())
    {
        return;
    }

    cv::Mat annotated = image.clone();

    int centerX = static_cast<int>(result.x);
    int centerY = static_cast<int>(result.y);
    int boxWidth = static_cast<int>(result.width);
    int boxHeight = static_cast<int>(result.height);

    int x1 = centerX - boxWidth / 2;
    int y1 = centerY - boxHeight / 2;
    int x2 = centerX + boxWidth / 2;
    int y2 = centerY + boxHeight / 2;

    cv::rectangle(
        annotated,
        cv::Point(x1, y1),
        cv::Point(x2, y2),
        cv::Scalar(0, 255, 0),
        2
    );

    std::string label =
        result.className + " " + std::to_string(result.confidence);

    cv::putText(
        annotated,
        label,
        cv::Point(x1, y1 - 10),
        cv::FONT_HERSHEY_SIMPLEX,
        0.7,
        cv::Scalar(0, 255, 0),
        2
    );

    cv::imwrite(outputPath, annotated);
}