#include "commit.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <sstream>

namespace fs = std::filesystem;

// Helper function to get the current timestamp
std::string getCurrentTimestamp() {
    std::time_t now = std::time(0);
    std::stringstream ss;
    ss << now;
    return ss.str();
}

// Helper function to generate a unique commit ID based on timestamp and index data
std::string generateCommitID(const std::string& indexData) {
    // Use the timestamp as part of the commit ID (can be replaced with a hash of file states for more uniqueness)
    return getCurrentTimestamp();
}

// Helper function to create the commit snapshot directory and copy the tracked files
bool createCommitSnapshot(const std::string& commitID) {
    std::string vcsIndexFile = ".vcs/index";
    std::string vcsCommitsDir = ".vcs/commits/" + commitID;


    if (!fs::exists(vcsIndexFile)) {
        std::cerr << "Error: No files are being tracked. Please track files before committing.\n";
        return false;
    }

    
    std::ifstream indexFile(vcsIndexFile);
    if (!indexFile) {
        std::cerr << "Error: Unable to open index file.\n";
        return false;
    }


    try {
        fs::create_directory(vcsCommitsDir);
        std::cout << "Created commit directory: " << vcsCommitsDir << "\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
        return false;
    }

  
    std::string line;
    while (std::getline(indexFile, line)) {
        std::istringstream iss(line);
        std::string filePath, fileHash;
        iss >> filePath >> fileHash;

     
        try {
            fs::copy(filePath, vcsCommitsDir + "/" + fs::path(filePath).filename().string(), fs::copy_options::overwrite_existing);
            std::cout << "Copied " << filePath << " to commit directory.\n";
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error copying file: " << e.what() << "\n";
            return false;
        }
    }

    return true;
}


void commitChanges(const std::string& commitMessage) {
    std::string vcsLogFile = ".vcs/log";
    std::string vcsIndexFile = ".vcs/index";

 
    if (!fs::exists(vcsIndexFile)) {
        std::cerr << "Error: No files are being tracked. Commit cannot proceed.\n";
        return;
    }

    std::ifstream indexFile(vcsIndexFile);
    std::string indexData((std::istreambuf_iterator<char>(indexFile)), std::istreambuf_iterator<char>());
    indexFile.close();

    std::string commitID = generateCommitID(indexData);

  
    if (!createCommitSnapshot(commitID)) {
        std::cerr << "Error: Failed to create commit snapshot. Commit aborted.\n";
        return;
    }

    
    std::ofstream logFile(vcsLogFile, std::ios::app);
    if (!logFile) {
        std::cerr << "Error: Unable to open log file for writing.\n";
        return;
    }

   
    std::string timestamp = getCurrentTimestamp();
    logFile << timestamp << " " << commitMessage << " " << commitID << "\n";
    logFile.close();

    std::cout << "Commit successful! Commit ID: " << commitID << "\n";
}
