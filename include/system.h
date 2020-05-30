#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   
  std::vector<Process>& Processes();  
  float MemoryUtilization();          
  long UpTime();                      
  int TotalProcesses();               
  int RunningProcesses();             
  std::string Kernel();               
  std::string OperatingSystem();      

 public:
  static std::vector<std::string> CurrCpuStats;
  static std::vector<std::string> PrevCpuStats;

 private:
  Processor m_Cpu = {};
  std::vector<Process> m_Processes = {};
};

#endif