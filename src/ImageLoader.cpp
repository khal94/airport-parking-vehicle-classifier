#include "ImageLoader.hpp"
#include <iostream>
#include <filesystem>

void ImageLoader::listImages(const char* folderPath)
{
    std::cout << "Reading images from: " << folderPath << std::endl;

    for (const auto& entry : std::filesystem::directory_iterator(folderPath))
    {
        if (entry.is_regular_file())
        {
            std::cout << "Found image: "
                      << entry.path().filename().string()
                      << std::endl;
        }
    }
}