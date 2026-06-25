#pragma once

#include <string>

struct DetectionResult
{
    std::string className;
    float confidence;

    float x;
    float y;
    float width;
    float height;
};