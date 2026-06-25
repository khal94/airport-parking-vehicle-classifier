#pragma once

#include <onnxruntime_cxx_api.h>
#include <opencv2/opencv.hpp>
#include "DetectionResult.hpp"

class OnnxEngine
{
public:
    bool initialize(const char* modelPath);
    DetectionResult predict(const cv::Mat& image);

private:
    Ort::Env env{ORT_LOGGING_LEVEL_WARNING, "AirportParkingClassifier"};

    Ort::SessionOptions sessionOptions;
    Ort::Session* session = nullptr;
};