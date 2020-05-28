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

// TODO: Return this process's ID
int Process::Pid() { return m_Pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    return 0; 
}

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(m_Pid); }

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(m_Pid); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(m_Pid); }

// Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(m_Pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }