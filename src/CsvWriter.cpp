#include "CsvWriter.hpp"
#include <fstream>

void CsvWriter::writeHeader(const char* filePath)
{
    std::ofstream file(filePath);

    file << "image_name,vehicle_type,confidence,price_eur,processing_time_ms,status\n";

    file.close();
}

void CsvWriter::appendRow(
    const char* filePath,
    const char* imageName,
    const char* vehicleType,
    float confidence,
    double priceEur,
    int processingTimeMs,
    const char* status
)
{
    std::ofstream file(filePath, std::ios::app);

    file
        << imageName << ","
        << vehicleType << ","
        << confidence << ","
        << priceEur << ","
        << processingTimeMs << ","
        << status << "\n";

    file.close();
}