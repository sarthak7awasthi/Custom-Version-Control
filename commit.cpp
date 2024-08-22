#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <sstream>
#include <openssl/sha.h>
#include <iomanip>

namespace fs = std::filesystem;

// Helper function to get the current timestamp
std::string getCurrentTimestamp() {
    std::time_t now = std::time(0);
    std::stringstream ss;
    ss << now;
    return ss.str();
}

// Helper function to compute SHA-1 hash of a string (for commit ID)
std::string computeSHA1Hash(const std::string& data) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA_CTX sha1;
    SHA1_Init(&sha1);
    SHA1_Update(&sha1, data.c_str(), data.size());
    SHA1_Final(hash, &sha1);

    std::stringstream hashStream;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        hashStream << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return hashStream.str();
}

// Function to generate a commit ID based on timestamp and file states
std::string generateCommitID(const std::string& indexData) {
    std::string timestamp = getCurrentTimestamp();
    std::string commitID = computeSHA1Hash(indexData + timestamp);
    return commitID;
}

// Function to create a commit
void commitChanges(const std::string& commitMessage) {
    std::string vcsIndexFile = ".vcs/index";
    std::string vcsLogFile = ".vcs/log";
    std::string vcsCommitsDir = ".vcs/commits/";

    // Check if the index file exists
    if (!fs::exists(vcsIndexFile)) {
        std::cerr << "Error: No files are being tracked. Please track files before committing.\n";
        return;
    }

    // Read the index file to find the tracked files
    std::ifstream indexFile(vcsIndexFile);
    if (!indexFile) {
        std::cerr << "Error: Unable to open index file.\n";
        return;
    }

    // Read the entire index file
    std::string indexData((std::istreambuf_iterator<char>(indexFile)), std::istreambuf_iterator<char>());
    indexFile.close();

    // Generate a unique commit ID
    std::string commitID = generateCommitID(indexData);

    // Create the commit directory
    std::string commitDir = vcsCommitsDir + commitID;
    if (fs::create_directory(commitDir)) {
        std::cout << "Created commit directory: " << commitDir << "\n";
    } else {
        std::cerr << "Error creating commit directory.\n";
        return;
    }

    // For each file in the index, copy it into the commit directory
    std::istringstream indexStream(indexData);
    std::string line;
    while (std::getline(indexStream, line)) {
        std::istringstream iss(line);
        std::string filePath, fileHash;
        iss >> filePath >> fileHash;

        // Copy the file into the commit directory
        fs::copy(filePath, commitDir + "/" + fs::path(filePath).filename().string(), fs::copy_options::overwrite_existing);
    }

    // Append commit metadata to the log file
    std::ofstream logFile(vcsLogFile, std::ios::app);
    if (!logFile) {
        std::cerr << "Error: Unable to open log file.\n";
        return;
    }

    std::string timestamp = getCurrentTimestamp();
    logFile << timestamp << " " << commitMessage << " " << commitID << "\n";
    logFile.close();

    std::cout << "Commit successful! Commit ID: " << commitID << "\n";
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: vcs commit <message>\n";
        return 1;
    }

    std::string command = argv[1];
    std::string commitMessage = argv[2];

    if (command == "commit") {
        commitChanges(commitMessage);
    } else {
        std::cerr << "Unknown command.\n";
    }

    return 0;
}
