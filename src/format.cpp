#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long SS = seconds % 60;
    long HH = seconds / 3600;
    long MM = (seconds / 60) - (HH * 60);
    return std::to_string(HH) + ":" + std::to_string(MM) + ":" + std::to_string(SS); 
}