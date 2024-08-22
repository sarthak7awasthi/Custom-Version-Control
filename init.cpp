#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void initializeRepository() {
 
    std::string vcsDir = ".vcs";
    std::string commitsDir = vcsDir + "/commits";
    std::string logFile = vcsDir + "/log";
    std::string indexFile = vcsDir + "/index";
    

    if (fs::exists(vcsDir)) {
        std::cout << "VCS repository already initialized.\n";
    } else {
        // Create the .vcs directory
        if (fs::create_directory(vcsDir)) {
            std::cout << "Created directory: " << vcsDir << "\n";
        } else {
            std::cerr << "Error creating .vcs directory.\n";
            return;
        }

        // Create the commits directory inside .vcs
        if (fs::create_directory(commitsDir)) {
            std::cout << "Created directory: " << commitsDir << "\n";
        } else {
            std::cerr << "Error creating commits directory.\n";
            return;
        }

        // Create the log file
        std::ofstream log(logFile);
        if (log) {
            std::cout << "Created log file: " << logFile << "\n";
        } else {
            std::cerr << "Error creating log file.\n";
            return;
        }
        log.close();

        // Create the index file
        std::ofstream index(indexFile);
        if (index) {
            std::cout << "Created index file: " << indexFile << "\n";
        } else {
            std::cerr << "Error creating index file.\n";
            return;
        }
        index.close();

        std::cout << "VCS repository initialized successfully.\n";
    }
}

int main() {
    initializeRepository();
    return 0;
}
