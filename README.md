# Custom Version Control System (VCS)

A simple version control system that allows you to track files, commit changes, view commit history, and restore previous versions of files. I made it to learn git in depth by implementing some of the functionalities.

## Features

- **Initialize a Repository**: Create a `.vcs` directory to store commit history and metadata.
- **Track Files**: Add files to version control for tracking changes.
- **Commit Changes**: Save the current state of tracked files with a message.
- **View Commit History**: See all previous commits with messages and timestamps.
- **Checkout a Commit**: Restore the project to a specific commit.

## Installation

### Requirements

- **CMake** (Version 3.10 or higher)
- **OpenSSL** (for SHA-1 hashing)
- **C++ compiler** (like G++)

### Build the Project

1. Clone the repository and navigate to the project folder.
2. Make the build script executable:
   ```bash
   chmod +x build.sh
   ```
3. Build the project using the script:
   ```bash
   ./build.sh build
   ```
### Usage

#### Commands

1. Initialize a Repository:
  ```bash
  ./build.sh init
  ```

2. Track a File:
  ```bash
  ./build.sh track <file>
  ```

3.Commit Changes:

  ```bash
  ./build.sh commit "<message>"
  ```

4. View Commit History:

  ```bash
  ./build.sh log
  ```

5. Checkout a Commit:

  ```bash
  ./build.sh checkout <commit_id>
  ```

### Directory Structure

After initializing a repository, the following structure will be created:

```perl
/YourProject
├── .vcs                # Stores VCS data
│   ├── commits/        # Stores file snapshots for each commit
│   ├── index           # Tracks the files added to VCS
│   └── log             # Stores commit information
├── main.cpp            # Example tracked file
└── README.md           # Example tracked file
```
