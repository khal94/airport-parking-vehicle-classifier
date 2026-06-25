#pragma once

#include <string>

class PricingEngine
{
public:
    static double calculatePrice(const std::string& vehicleType);
};