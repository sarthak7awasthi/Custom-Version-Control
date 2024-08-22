#ifndef INIT_H
#define INIT_H

#include <string>

// Function to initialize the repository
void initializeRepository();

// Helper function to create a directory with error checking
bool createDirectory(const std::string& dirPath);

// Helper function to create a file with error checking
bool createFile(const std::string& filePath);

#endif // INIT_H
