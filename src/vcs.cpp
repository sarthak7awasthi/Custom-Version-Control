#include <iostream>
#include <string>
#include <cstdlib>

#include "init.h"
#include "track.h"
#include "commit.h"
#include "log.h"
#include "checkout.h"

// Helper function to print usage instructions
void printUsage() {
    std::cout << "Usage: vcs <command> [options]\n";
    std::cout << "Available commands:\n";
    std::cout << "  init                   Initialize a new VCS repository\n";
    std::cout << "  track <file>            Track a file for version control\n";
    std::cout << "  commit <message>        Commit the current state of tracked files with a message\n";
    std::cout << "  log                    View the commit history\n";
    std::cout << "  checkout <commit_id>    Restore the project to a specific commit state\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Missing command.\n";
        printUsage();
        return 1;
    }

    std::string command = argv[1];

    if (command == "init") {
   
        initializeRepository();
    } else if (command == "track") {
        if (argc != 3) {
            std::cerr << "Error: Missing file argument for track command.\n";
            printUsage();
            return 1;
        }
        std::string filePath = argv[2];
    
        trackFile(filePath);
    } else if (command == "commit") {
        if (argc != 3) {
            std::cerr << "Error: Missing commit message.\n";
            printUsage();
            return 1;
        }
        std::string commitMessage = argv[2];

        commitChanges(commitMessage);
    } else if (command == "log") {
  
        viewHistory();
    } else if (command == "checkout") {
        if (argc != 3) {
            std::cerr << "Error: Missing commit ID.\n";
            printUsage();
            return 1;
        }
        std::string commitID = argv[2];
   
        checkoutCommit(commitID);
    } else {
        std::cerr << "Error: Unknown command '" << command << "'.\n";
        printUsage();
        return 1;
    }

    return 0;
}
