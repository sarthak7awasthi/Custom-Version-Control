#ifndef LOG_H
#define LOG_H

#include <vector>     
#include <string>     

// Function to display the commit history
void viewHistory();

// Helper function to read and parse the log file
std::vector<std::string> readLogEntries();

#endif // LOG_H
