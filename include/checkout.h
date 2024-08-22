#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <string>

// Function to restore the project to a specific commit state
void checkoutCommit(const std::string& commitID);

// Helper function to verify if a commit exists
bool commitExists(const std::string& commitID);

#endif // CHECKOUT_H
