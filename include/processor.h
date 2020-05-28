#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  

 private:
  void CalculateCurrentCpuStats();
  void CalculatePrevCpuStats();

 private:
  float m_User, m_Nice, m_Idle, m_Sys, m_Virtual, m_Total;
  float m_PrevUser, m_PrevNice, m_PrevIdle, m_PrevSys, m_PrevVirtual, m_PrevTotal;
};

#endif