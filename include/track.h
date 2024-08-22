#ifndef TRACK_H
#define TRACK_H

#include <string>

// Function to track a file and add its hash to the .vcs/index
void trackFile(const std::string& filePath);

// Helper function to compute the SHA-1 hash of a file
std::string computeSHA1Hash(const std::string& filePath);

// Helper function to check if a file is already being tracked
bool isFileTracked(const std::string& filePath);

#endif // TRACK_H
