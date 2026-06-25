#include "PricingEngine.hpp"

double PricingEngine::calculatePrice(const std::string& vehicleType)
{
    if (vehicleType == "moto")
    {
        return 2.0;
    }

    if (vehicleType == "auto")
    {
        return 5.0;
    }

    if (vehicleType == "camionette")
    {
        return 7.0;
    }

    if (vehicleType == "bus")
    {
        return 10.0;
    }

    return 0.0;
}