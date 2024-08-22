#ifndef COMMIT_H
#define COMMIT_H

#include <string>

// Function to commit the current state of the tracked files
void commitChanges(const std::string& commitMessage);

// Helper function to generate a unique commit ID based on the index data and timestamp
std::string generateCommitID(const std::string& indexData);

// Helper function to create a snapshot of the tracked files in the commit directory
bool createCommitSnapshot(const std::string& commitID);

#endif // COMMIT_H
