#include "processor.h"
#include "linux_parser.h"

#include <vector>
#include <string>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::vector<std::string> cpu_stats = LinuxParser::CpuUtilization();

    float user_time = std::stof(cpu_stats[0]) - std::stof(cpu_stats[8]);
    float nice_time = std::stof(cpu_stats[1]) - std::stof(cpu_stats[9]);
    float idle_all_time = std::stof(cpu_stats[3]) - std::stof(cpu_stats[4]);
    float sys_all_time = std::stof(cpu_stats[2]) + std::stof(cpu_stats[5]) + std::stof(cpu_stats[6]);
    float virtual_time = std::stof(cpu_stats[8]) - std::stof(cpu_stats[9]);
    float total_time = std::stof(cpu_stats[7]) + user_time + nice_time + idle_all_time + sys_all_time + virtual_time;

    // TODO: Calculate Percentage . . .
    return 0.0; 
}