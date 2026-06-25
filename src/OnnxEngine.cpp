#include "OnnxEngine.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

static const std::vector<std::string> CLASS_NAMES = {
    "ambulance",
    "army vehicle",
    "auto rickshaw",
    "bicycle",
    "bus",
    "car",
    "garbagevan",
    "human hauler",
    "minibus",
    "minivan",
    "motorbike",
    "pickup",
    "policecar",
    "rickshaw",
    "scooter",
    "suv",
    "taxi",
    "three wheelers -CNG-",
    "truck",
    "van",
    "wheelbarrow"
};

static std::string mapToClientCategory(const std::string& cls)
{
    if (
        cls == "car" ||
        cls == "taxi" ||
        cls == "suv" ||
        cls == "ambulance" ||
        cls == "policecar"
    )
    {
        return "auto";
    }

    if (
        cls == "motorbike" ||
        cls == "scooter" ||
        cls == "bicycle"
    )
    {
        return "moto";
    }

    if (
        cls == "pickup" ||
        cls == "van" ||
        cls == "minivan"
    )
    {
        return "camionette";
    }

    if (
        cls == "bus" ||
        cls == "minibus"
    )
    {
        return "bus";
    }

    return "unknown";
}

bool OnnxEngine::initialize(const char* modelPath)
{
    try
    {
        sessionOptions.SetIntraOpNumThreads(1);

        std::wstring wideModelPath;
        std::string modelPathStr(modelPath);
        wideModelPath.assign(modelPathStr.begin(), modelPathStr.end());

        session = new Ort::Session(
            env,
            wideModelPath.c_str(),
            sessionOptions
        );

        std::cout << "Model loaded successfully: "
                  << modelPath << std::endl;

        return true;
    }
    catch (const Ort::Exception& e)
    {
        std::cerr << "ONNX Runtime Error: "
                  << e.what() << std::endl;

        return false;
    }
}

DetectionResult OnnxEngine::predict(const cv::Mat& image)
{
    DetectionResult result;
    result.className = "unknown";
    result.confidence = 0.0f;

    result.x = 0.0f;
    result.y = 0.0f;
    result.width = 0.0f;
    result.height = 0.0f;

    if (image.empty())
    {
        result.className = "invalid_image";
        return result;
    }

    cv::Mat resized;
    cv::resize(image, resized, cv::Size(640, 640));

    cv::Mat floatImage;
    resized.convertTo(floatImage, CV_32F, 1.0 / 255.0);

    std::vector<float> inputTensorValues;
    inputTensorValues.reserve(1 * 3 * 640 * 640);

    for (int c = 0; c < 3; ++c)
    {
        for (int y = 0; y < 640; ++y)
        {
            for (int x = 0; x < 640; ++x)
            {
                inputTensorValues.push_back(
                    floatImage.at<cv::Vec3f>(y, x)[c]
                );
            }
        }
    }

    std::array<int64_t, 4> inputShape = {1, 3, 640, 640};

    Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(
        OrtArenaAllocator,
        OrtMemTypeDefault
    );

    Ort::Value inputTensor = Ort::Value::CreateTensor<float>(
        memoryInfo,
        inputTensorValues.data(),
        inputTensorValues.size(),
        inputShape.data(),
        inputShape.size()
    );

    Ort::AllocatorWithDefaultOptions allocator;

    auto inputNameAllocated = session->GetInputNameAllocated(0, allocator);
    auto outputNameAllocated = session->GetOutputNameAllocated(0, allocator);

    const char* inputNames[] = { inputNameAllocated.get() };
    const char* outputNames[] = { outputNameAllocated.get() };

    auto outputTensors = session->Run(
        Ort::RunOptions{nullptr},
        inputNames,
        &inputTensor,
        1,
        outputNames,
        1
    );

    float* outputData = outputTensors[0].GetTensorMutableData<float>();

    // YOLO output shape: [1, 25, 8400]
    const int numClasses = 21;
    const int numPredictions = 8400;
    const int elementsPerPrediction = 25;

    float bestConfidence = 0.0f;
    int bestClassId = -1;
    int bestPredictionIndex = -1;

    for (int i = 0; i < numPredictions; ++i)
    {
        for (int classId = 0; classId < numClasses; ++classId)
        {
            float confidence = outputData[(4 + classId) * numPredictions + i];

            if (confidence > bestConfidence)
            {
                bestConfidence = confidence;
                bestClassId = classId;
                bestPredictionIndex = i;
            }
        }
    }

    if (bestClassId >= 0 && bestClassId < CLASS_NAMES.size())
{
    result.confidence = bestConfidence;

    if (bestConfidence >= 0.50f)
    {
        result.className =
            mapToClientCategory(
                CLASS_NAMES[bestClassId]
    );
    
    }
    else
    {
        result.className = "unknown";
    }
}

    if (bestPredictionIndex >= 0)
{
    result.x = outputData[0 * numPredictions + bestPredictionIndex];
    result.y = outputData[1 * numPredictions + bestPredictionIndex];
    result.width = outputData[2 * numPredictions + bestPredictionIndex];
    result.height = outputData[3 * numPredictions + bestPredictionIndex];
}

    return result;
}