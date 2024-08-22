#include <iostream>
#include <fstream>
#include <filesystem>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

// Helper function to compute SHA-1 hash of a file
std::string computeSHA1Hash(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Unable to open file " << filePath << "\n";
        return "";
    }

    // Buffer to read file contents
    char buffer[8192];
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA_CTX sha1;
    SHA1_Init(&sha1);

    // Read file and update hash
    while (file.read(buffer, sizeof(buffer))) {
        SHA1_Update(&sha1, buffer, file.gcount());
    }
    SHA1_Update(&sha1, buffer, file.gcount());

    // Finalize the SHA1 hash
    SHA1_Final(hash, &sha1);

    // Convert the hash to a hex string
    std::stringstream hashStream;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        hashStream << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return hashStream.str();
}

// Function to track a file (add its hash to .vcs/index)
void trackFile(const std::string& filePath) {
    std::string vcsIndexFile = ".vcs/index";

    // Check if the file exists
    if (!fs::exists(filePath)) {
        std::cerr << "Error: File " << filePath << " does not exist.\n";
        return;
    }

    // Compute the file's hash
    std::string fileHash = computeSHA1Hash(filePath);
    if (fileHash.empty()) {
        std::cerr << "Error: Unable to compute hash for " << filePath << "\n";
        return;
    }

    // Open the .vcs/index file to append the tracked file and its hash
    std::ofstream indexFile(vcsIndexFile, std::ios::app);
    if (!indexFile) {
        std::cerr << "Error: Unable to open " << vcsIndexFile << "\n";
        return;
    }

    indexFile << filePath << " " << fileHash << "\n";
    indexFile.close();

    std::cout << "File " << filePath << " is now being tracked.\n";
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: vcs track <file>\n";
        return 1;
    }

    std::string command = argv[1];
    std::string filePath = argv[2];

    if (command == "track") {
        trackFile(filePath);
    } else {
        std::cerr << "Unknown command.\n";
    }

    return 0;
}
