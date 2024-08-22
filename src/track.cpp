#include "track.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;


std::string computeSHA1Hash(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Unable to open file: " << filePath << "\n";
        return "";
    }


    char buffer[8192];
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA_CTX sha1;
    SHA1_Init(&sha1);


    while (file.read(buffer, sizeof(buffer))) {
        SHA1_Update(&sha1, buffer, file.gcount());
    }
    SHA1_Update(&sha1, buffer, file.gcount());

 
    SHA1_Final(hash, &sha1);


    std::stringstream hashStream;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        hashStream << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return hashStream.str();
}


bool isFileTracked(const std::string& filePath) {
    std::string vcsIndexFile = ".vcs/index";

  
    if (!fs::exists(vcsIndexFile)) {
        return false; 
    }

    std::ifstream indexFile(vcsIndexFile);
    std::string line;

  
    while (std::getline(indexFile, line)) {
        if (line.find(filePath) == 0) { 
            return true;
        }
    }

    return false;
}


void trackFile(const std::string& filePath) {
    std::string vcsIndexFile = ".vcs/index";


    if (!fs::exists(filePath)) {
        std::cerr << "Error: File " << filePath << " does not exist.\n";
        return;
    }


    if (isFileTracked(filePath)) {
        std::cout << "File " << filePath << " is already being tracked.\n";
        return;
    }


    std::string fileHash = computeSHA1Hash(filePath);
    if (fileHash.empty()) {
        std::cerr << "Error: Unable to compute hash for " << filePath << "\n";
        return;
    }

 
    std::ofstream indexFile(vcsIndexFile, std::ios::app);
    if (!indexFile) {
        std::cerr << "Error: Unable to open " << vcsIndexFile << "\n";
        return;
    }

 
    indexFile << filePath << " " << fileHash << "\n";
    indexFile.close();

    std::cout << "File " << filePath << " is now being tracked.\n";
}
