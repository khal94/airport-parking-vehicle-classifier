#pragma once

#include "OnnxEngine.hpp"
#include "ConfigManager.hpp"

class InferenceEngine
{
public:
    static void processImages(
        OnnxEngine& engine,
        const AppConfig& config
    );
};