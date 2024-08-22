#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

// Function to perform the checkout (rollback) operation
void checkoutCommit(const std::string& commitID) {
    std::string vcsCommitsDir = ".vcs/commits/";
    std::string commitDir = vcsCommitsDir + commitID;

    // Check if the commit directory exists
    if (!fs::exists(commitDir)) {
        std::cerr << "Error: Commit ID " << commitID << " does not exist.\n";
        return;
    }

    // Iterate through the files in the commit directory and copy them to the working directory
    for (const auto& entry : fs::directory_iterator(commitDir)) {
        const auto& commitFilePath = entry.path();
        const auto& fileName = commitFilePath.filename();
        
        // Copy the file from the commit directory to the working directory
        std::string destPath = fileName.string();
        fs::copy(commitFilePath, destPath, fs::copy_options::overwrite_existing);
        std::cout << "Restored: " << fileName << " to the working directory.\n";
    }

    std::cout << "Project rolled back to commit: " << commitID << "\n";
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: vcs checkout <commit_id>\n";
        return 1;
    }

    std::string command = argv[1];
    std::string commitID = argv[2];

    if (command == "checkout") {
        checkoutCommit(commitID);
    } else {
        std::cerr << "Unknown command.\n";
    }

    return 0;
}
