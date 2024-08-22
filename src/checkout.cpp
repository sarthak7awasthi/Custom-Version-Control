#include "checkout.h"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

// Helper function to verify if a commit exists
bool commitExists(const std::string& commitID) {
    std::string commitDir = ".vcs/commits/" + commitID;
    return fs::exists(commitDir);
}

// Function to restore the project to a specific commit state
void checkoutCommit(const std::string& commitID) {
    std::string commitDir = ".vcs/commits/" + commitID;

    // Check if the commit directory exists
    if (!commitExists(commitID)) {
        std::cerr << "Error: Commit ID " << commitID << " does not exist.\n";
        return;
    }

    // Iterate through the files in the commit directory and restore them to the working directory
    for (const auto& entry : fs::directory_iterator(commitDir)) {
        const auto& commitFilePath = entry.path();
        const auto& fileName = commitFilePath.filename();

        try {
            // Restore the file from the commit directory to the working directory
            fs::copy(commitFilePath, fileName, fs::copy_options::overwrite_existing);
            std::cout << "Restored: " << fileName << " to the working directory.\n";
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error restoring file: " << e.what() << "\n";
        }
    }

    std::cout << "Project rolled back to commit: " << commitID << "\n";
}
