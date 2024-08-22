#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void viewHistory() {
    std::string vcsLogFile = ".vcs/log";

    // Check if the log file exists
    if (!std::ifstream(vcsLogFile)) {
        std::cerr << "Error: No commit history found. Please make a commit first.\n";
        return;
    }

    // Open the log file
    std::ifstream logFile(vcsLogFile);
    if (!logFile) {
        std::cerr << "Error: Unable to open log file.\n";
        return;
    }

    // Read all log entries into a vector
    std::vector<std::string> logEntries;
    std::string line;
    while (std::getline(logFile, line)) {
        logEntries.push_back(line);
    }
    logFile.close();

    // If there are no log entries
    if (logEntries.empty()) {
        std::cout << "No commits have been made yet.\n";
        return;
    }

    // Display log entries in reverse chronological order
    std::cout << "Commit History:\n";
    for (auto it = logEntries.rbegin(); it != logEntries.rend(); ++it) {
        std::cout << *it << "\n";
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: vcs log\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "log") {
        viewHistory();
    } else {
        std::cerr << "Unknown command.\n";
    }

    return 0;
}
