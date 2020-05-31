#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <unistd.h>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Reads and return the system memory utilization
vector<float> LinuxParser::MemoryUtilization() { 
  float mem_total, mem_free, mem_cached, mem_sh, buffers, s_reclaim;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);

  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      string key, value;
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> key >> value;

      if (key == "MemTotal") {
        mem_total = stof(value);
      } else if (key == "MemFree") {
        mem_free = stof(value);
      } else if (key == "Buffers") {
        buffers = stof(value);
      } else if (key == "Cached") {
        mem_cached = stof(value);
      } else if (key == "Shmem") {
        mem_sh = stof(value);
      } else if (key == "SReclaimable") {
        s_reclaim = stof(value);
        break;
      }
    }
  }

  float total_memory_usage = mem_total - mem_free;
  float cached_memory = mem_cached + s_reclaim - mem_sh;

  float mem_usage = (total_memory_usage - (buffers + cached_memory));

  vector<float> mem_data = {(mem_usage / mem_total), mem_usage, buffers, cached_memory};

  return mem_data; 
}

// Reads and return the system uptime
long LinuxParser::UpTime() { 
  string sys_uptime, idle_uptime;

  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> sys_uptime >> idle_uptime;
  }
  return std::stol(sys_uptime);// + std::stol(idle_uptime); 
}

// Reads and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  vector<string> cpu_stats = CpuUtilization();
  long system_time = std::stol(cpu_stats[2]) 
                   + std::stol(cpu_stats[5])
                   + std::stol(cpu_stats[6]);
                   
  return system_time * sysconf(_SC_CLK_TCK); 
}

// Reads and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) { 
  vector<string> pid_stats;
  string line, value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while(linestream >> value) pid_stats.push_back(value);
  }

  long total_time = std::stol(pid_stats[13]) + std::stol(pid_stats[14]);

  return total_time / sysconf(_SC_CLK_TCK);
}

// Reads and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  vector<string> cpu_stats = CpuUtilization();
  long active_time = std::stol(cpu_stats[0]) + std::stol(cpu_stats[8])
                   + std::stol(cpu_stats[1]) + std::stol(cpu_stats[9]);
  long system_time = std::stol(cpu_stats[2]) 
                   + std::stol(cpu_stats[5])
                   + std::stol(cpu_stats[6]);

  active_time += system_time + std::stol(cpu_stats[7]);
  return active_time * sysconf(_SC_CLK_TCK); 
}

// Reads and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  vector<string> cpu_stats = CpuUtilization();
  long idle_time = std::stol(cpu_stats[3]) + std::stol(cpu_stats[4]);
  return idle_time * sysconf(_SC_CLK_TCK); 
}

// Reads and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpu_stats;
  string line, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> value) { if (value == "cpu") continue; cpu_stats.push_back(value); }
  }
  return cpu_stats;
}

// Reads and returns the total number of processes
int LinuxParser::TotalProcesses() { 
  string line, key, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;

      if (key == "processes") {
        break;
      }
    }
  }

  return stoi(value); 
}

// Reads and returns the number of running processes
int LinuxParser::RunningProcesses() { 
  string line, key, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;

      if (key == "procs_running") {
        break;
      }
    }
  }

  return stoi(value);  
}

// Reads and return the command associated with a process
string LinuxParser::Command(int pid) { 
  string cmd_line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, cmd_line);
  }
  return cmd_line; 
}

// Reads and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  string line, key, value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;

      if (key == "VmSize:") {
        break;
      }
    }
  }

  long memory = std::stol(value) * 0.001; // Convert from kB to mB

  return std::to_string(memory);
}

// Reads and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  string line, key, value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> key >> value;

      if (key == "Uid") {
        break;
      }
    }
  }
  
  return value; 
}

// Reads and return the user associated with a process
string LinuxParser::User(int pid) { 
  string user_id = Uid(pid);
  string line, name;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> name;

      if (name == user_id) {
        break;
      }
    }
  }
  return name;
}

// Reads and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
  vector<string> pid_stats;
  string line, value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while(linestream >> value) pid_stats.push_back(value);
  }
  
  return std::stol(pid_stats[21]) / sysconf(_SC_CLK_TCK);
}