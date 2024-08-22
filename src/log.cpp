#include "log.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Helper function to read and parse the log file
std::vector<std::string> readLogEntries() {
    std::string vcsLogFile = ".vcs/log";
    std::vector<std::string> logEntries;


    std::ifstream logFile(vcsLogFile);
    if (!logFile) {
        std::cerr << "Error: No commit history found. Please make a commit first.\n";
        return logEntries;
    }

    
    std::string line;
    while (std::getline(logFile, line)) {
        logEntries.push_back(line);
    }
    logFile.close();

    return logEntries;
}

void viewHistory() {
    std::vector<std::string> logEntries = readLogEntries();


    if (logEntries.empty()) {
        std::cout << "No commits have been made yet.\n";
        return;
    }

   
    std::cout << "Commit History:\n";
    for (auto it = logEntries.rbegin(); it != logEntries.rend(); ++it) {
        std::cout << *it << "\n";
    }
}
