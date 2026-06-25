#include "ConfigManager.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

static std::string extractString(
    const std::string& content,
    const std::string& key
)
{
    std::string pattern = "\"" + key + "\"";
    size_t keyPos = content.find(pattern);

    if (keyPos == std::string::npos)
    {
        return "";
    }

    size_t colonPos = content.find(":", keyPos);
    size_t firstQuote = content.find("\"", colonPos + 1);
    size_t secondQuote = content.find("\"", firstQuote + 1);

    return content.substr(firstQuote + 1, secondQuote - firstQuote - 1);
}

static float extractFloat(
    const std::string& content,
    const std::string& key
)
{
    std::string pattern = "\"" + key + "\"";
    size_t keyPos = content.find(pattern);

    if (keyPos == std::string::npos)
    {
        return 0.0f;
    }

    size_t colonPos = content.find(":", keyPos);
    size_t endPos = content.find_first_of(",}", colonPos + 1);

    return std::stof(content.substr(colonPos + 1, endPos - colonPos - 1));
}

static int extractInt(
    const std::string& content,
    const std::string& key
)
{
    return static_cast<int>(
        extractFloat(content, key)
    );
}

bool ConfigManager::loadConfig(
    const char* configPath,
    AppConfig& config
)
{
    std::ifstream file(configPath);

    if (!file)
    {
        std::cerr << "Failed to open config file: "
                  << configPath << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string content = buffer.str();

    config.modelPath = extractString(content, "model_path");
    config.inputFolder = extractString(content, "input_folder");
    config.outputCsv = extractString(content, "output_csv");
    config.outputFolder = extractString(content, "output_folder");
    config.confidenceThreshold = extractFloat(content, "confidence_threshold");
    config.imageSize = extractInt(content, "image_size");

    std::cout << "Config loaded successfully." << std::endl;

    return true;
}