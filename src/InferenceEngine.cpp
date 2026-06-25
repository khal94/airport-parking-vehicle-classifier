#include "InferenceEngine.hpp"
#include "CsvWriter.hpp"
#include "ImageProcessor.hpp"
#include "ResultVisualizer.hpp"
#include "Logger.hpp"
#include "PricingEngine.hpp"

#include <iostream>
#include <filesystem>
#include <chrono>

void InferenceEngine::processImages(
    OnnxEngine& engine,
    const AppConfig& config
)
{
    const char* inputFolder = config.inputFolder.c_str();
    const char* outputCsv = config.outputCsv.c_str();

    std::cout << "Processing images one by one..." << std::endl;
    Logger::info("Processing images one by one");

    for (const auto& entry : std::filesystem::directory_iterator(inputFolder))
    {
        if (entry.is_regular_file())
        {
            auto start = std::chrono::high_resolution_clock::now();

            std::string imageName = entry.path().filename().string();
            std::string imageStem = entry.path().stem().string();
            std::string imagePath = std::filesystem::absolute(entry.path()).string();

            cv::Mat image = ImageProcessor::loadImage(imagePath.c_str());
            DetectionResult prediction = engine.predict(image);
            double estimatedPrice =
                PricingEngine::calculatePrice(
                    prediction.className
                    );

            std::string outputImagePath =
                config.outputFolder + "/" + imageStem + "_result.jpg";

            ResultVisualizer::saveAnnotatedImage(
                image,
                prediction,
                outputImagePath.c_str()
            );

            auto end = std::chrono::high_resolution_clock::now();

            int processingTimeMs =
                std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            const char* status = "success";

            if (prediction.className == "unknown")
            {
                status = "low_confidence";

                Logger::warning(
                    "Low confidence prediction for image: " + imageName
                );
            }

            CsvWriter::appendRow(
                outputCsv,
                imageName.c_str(),
                prediction.className.c_str(),
                prediction.confidence,
                estimatedPrice,
                processingTimeMs,
                status
            );

            std::cout << "Processed: "
                      << imageName
                      << " | prediction="
                      << prediction.className
                      << " | price="
                      << estimatedPrice
                      << " EUR"
                      << std::endl;

            Logger::info(
                "Processed image: " + imageName +
                " | prediction=" + prediction.className +
                " | confidence=" + std::to_string(prediction.confidence)
            );
        }
    }
}