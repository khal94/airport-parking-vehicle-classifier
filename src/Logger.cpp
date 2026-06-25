#include "Logger.hpp"

#include <fstream>
#include <iostream>

static const char* LOG_FILE = "../logs/app.log";

static void writeLog(
    const std::string& level,
    const std::string& message
)
{
    std::ofstream file(LOG_FILE, std::ios::app);

    file << "[" << level << "] "
         << message << "\n";

    file.close();
}

void Logger::info(const std::string& message)
{
    writeLog("INFO", message);
}

void Logger::warning(const std::string& message)
{
    writeLog("WARNING", message);
}

void Logger::error(const std::string& message)
{
    writeLog("ERROR", message);
}