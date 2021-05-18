#include <sstream>
#include <iomanip>

#include "utility.h"

std::string MinutesToDaytime(std::chrono::minutes minutes)
{
    std::stringstream ss;
    auto hours = std::chrono::duration_cast<std::chrono::hours>(minutes);
    ss << std::setw(2) << std::setfill('0') << hours.count() << ":"
       << std::setw(2) << std::setfill('0') << (minutes - hours).count();
    return ss.str();
}
