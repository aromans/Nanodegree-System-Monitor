#include "processor.h"
#include "system.h"

#include <iostream>
#include <vector>
#include <string>

// Returns the aggregate CPU utilization
float Processor::Utilization() { 

    CalculateCurrentCpuStats();
    CalculatePrevCpuStats();

    float total_tally = m_Total - m_PrevTotal;
    float idle_tally = m_Idle - m_PrevIdle;

    // Calculate Percentage . . .
    return (total_tally - idle_tally) / total_tally; 
}

void Processor::CalculateCurrentCpuStats() {
    std::vector<std::string> cpu_stats = System::CurrCpuStats;
    if (cpu_stats.size() <= 0) return;

    m_User    = std::stof(cpu_stats[0]) - std::stof(cpu_stats[8]);
    m_Nice    = std::stof(cpu_stats[1]) - std::stof(cpu_stats[9]);
    m_Idle    = std::stof(cpu_stats[3]) - std::stof(cpu_stats[4]);
    m_Sys     = std::stof(cpu_stats[2]) + std::stof(cpu_stats[5]) + std::stof(cpu_stats[6]);
    m_Virtual = std::stof(cpu_stats[8]) - std::stof(cpu_stats[9]);
    m_Total   = std::stof(cpu_stats[7]) + m_User + m_Nice + m_Idle + m_Sys + m_Virtual;
}

void Processor::CalculatePrevCpuStats() {
    std::vector<std::string> prev_cpu_stats = System::PrevCpuStats;
    if (prev_cpu_stats.size() <= 0) return;

    m_PrevUser    = std::stof(prev_cpu_stats[0]) - std::stof(prev_cpu_stats[8]);
    m_PrevNice    = std::stof(prev_cpu_stats[1]) - std::stof(prev_cpu_stats[9]);
    m_PrevIdle    = std::stof(prev_cpu_stats[3]) - std::stof(prev_cpu_stats[4]);
    m_PrevSys     = std::stof(prev_cpu_stats[2]) + std::stof(prev_cpu_stats[5]) + std::stof(prev_cpu_stats[6]);
    m_PrevVirtual = std::stof(prev_cpu_stats[8]) - std::stof(prev_cpu_stats[9]);
    m_PrevTotal   = std::stof(prev_cpu_stats[7]) + m_PrevUser + m_PrevNice + m_PrevIdle + m_PrevSys + m_PrevVirtual;
}