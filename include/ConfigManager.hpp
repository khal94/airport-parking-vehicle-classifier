#pragma once

#include <string>

struct AppConfig
{
    std::string modelPath;
    std::string inputFolder;
    std::string outputCsv;
    std::string outputFolder;

    float confidenceThreshold;
    int imageSize;
};

class ConfigManager
{
public:
    static bool loadConfig(
        const char* configPath,
        AppConfig& config
    );
};