#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

vector<string> System::CurrCpuStats = {};
vector<string> System::PrevCpuStats = {};

// Returns the system's CPU
Processor& System::Cpu() { 
    if (CurrCpuStats.size() > 0) PrevCpuStats = CurrCpuStats;
    CurrCpuStats = LinuxParser::CpuUtilization();
    cpu_.Utilization();
    return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// Returns the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// Returns the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// Returns the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// Returns the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }