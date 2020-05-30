#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "format.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Returns this process's ID
int Process::Pid() { return m_Pid; }

// Returns this process's CPU utilization
float Process::CpuUtilization() { 
    float total = m_SystemCpu.GetTotal() - m_SystemCpu.GetPrevTotal();
    m_CpuPercentage = (LinuxParser::ActiveJiffies(m_Pid)) / total;
    return m_CpuPercentage; 
}

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(m_Pid); }

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(m_Pid); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(m_Pid); }

// Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(m_Pid); }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { 
    return a.m_CpuPercentage < m_CpuPercentage;
}