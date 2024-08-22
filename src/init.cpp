#include "init.h"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

// Function to create a directory, with error checking
bool createDirectory(const std::string& dirPath) {
    if (fs::exists(dirPath)) {
        std::cout << "Directory already exists: " << dirPath << "\n";
        return true;
    }

    try {
        if (fs::create_directory(dirPath)) {
            std::cout << "Successfully created directory: " << dirPath << "\n";
            return true;
        } else {
            std::cerr << "Error: Unable to create directory: " << dirPath << "\n";
            return false;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
        return false;
    }
}

// Function to create a file, with error checking
bool createFile(const std::string& filePath) {
    if (fs::exists(filePath)) {
        std::cout << "File already exists: " << filePath << "\n";
        return true;
    }

    std::ofstream file(filePath);
    if (file) {
        std::cout << "Successfully created file: " << filePath << "\n";
        return true;
    } else {
        std::cerr << "Error: Unable to create file: " << filePath << "\n";
        return false;
    }
}

// Main function to initialize the repository
void initializeRepository() {
    // Define the VCS directories and files
    std::string vcsDir = ".vcs";
    std::string commitsDir = vcsDir + "/commits";
    std::string logFile = vcsDir + "/log";
    std::string indexFile = vcsDir + "/index";

    // Check if the VCS repository has already been initialized
    if (fs::exists(vcsDir)) {
        std::cout << "VCS repository already initialized at: " << vcsDir << "\n";
        return;
    }

    // Create the .vcs directory
    if (!createDirectory(vcsDir)) {
        std::cerr << "Failed to initialize VCS repository. Exiting...\n";
        return;
    }

    // Create the commits subdirectory inside .vcs
    if (!createDirectory(commitsDir)) {
        std::cerr << "Failed to create commits directory. Exiting...\n";
        return;
    }

    // Create the log file in the .vcs directory
    if (!createFile(logFile)) {
        std::cerr << "Failed to create log file. Exiting...\n";
        return;
    }

    // Create the index file in the .vcs directory
    if (!createFile(indexFile)) {
        std::cerr << "Failed to create index file. Exiting...\n";
        return;
    }

    std::cout << "VCS repository successfully initialized at: " << vcsDir << "\n";
}
