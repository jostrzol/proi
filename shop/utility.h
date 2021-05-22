#pragma once

#include <string>
#include <chrono>

// Returns the given duration in <Hours>:<Minutes> format
std::string MinutesToDaytime(std::chrono::minutes minutes);