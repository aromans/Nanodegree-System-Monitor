#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  void SetPid(const int& pid) { m_Pid = pid; }
  void SetUser(const std::string& user) { m_UserName = user; }
  void SetCmd(const std::string& command) { m_Command = command; }
  void SetCpuUsage(const float& usage) { m_CpuUsage = usage; }
  void SetRamUsage(const std::string& usage) { m_RamUsage = usage + " mB"; }
  void SetUpTime(const long int& up_time) { m_UpTime = up_time; }

  // TODO: Declare any necessary private members
 private:
  int m_Pid;
  std::string m_UserName;
  std::string m_Command;
  float m_CpuUsage;
  std::string m_RamUsage;
  long int m_UpTime;
};

#endif