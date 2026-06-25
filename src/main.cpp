#include <iostream>

#include "ConfigManager.hpp"
#include "InferenceEngine.hpp"
#include "CsvWriter.hpp"
#include "ImageLoader.hpp"
#include "OnnxEngine.hpp"
#include "Logger.hpp"
#include "OracleImageReader.hpp"

int main()
{
    std::cout << "Airport Parking Classifier - Prototype 1" << std::endl;

    Logger::info(
    "Application started"
);

    OracleImageReader::connect();

    AppConfig config;

    if (!ConfigManager::loadConfig(
            "../config/config.json",
            config))
    {
        std::cerr << "Failed to load configuration." << std::endl;
        return 1;
    }

    OnnxEngine engine;

    if (!engine.initialize(config.modelPath.c_str()))
    {
        std::cerr << "Failed to initialize ONNX engine." << std::endl;
        return 1;
    }

    CsvWriter::writeHeader(
        config.outputCsv.c_str()
    );

    ImageLoader::listImages(
        config.inputFolder.c_str()
    );

    InferenceEngine::processImages(
        engine,
        config
    );

    std::cout << "Application finished successfully." << std::endl;

    return 0;
}