#pragma once

class CsvWriter
{
public:
    static void writeHeader(const char* filePath);

    static void appendRow(
        const char* filePath,
        const char* imageName,
        const char* vehicleType,
        float confidence,
        double priceEur,
        int processingTimeMs,
        const char* status
    );
};