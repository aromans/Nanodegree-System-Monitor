#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "processor.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(const int& pid, const Processor& cpu) : m_Pid(pid), m_SystemCpu(cpu) {}

  // Getters
  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process const& a) const;  

 private:
  int m_Pid;
  Processor m_SystemCpu;
  float m_CpuPercentage;
};

#endif