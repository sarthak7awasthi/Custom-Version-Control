#!/bin/bash


print_usage() {
    echo "Usage: $0 <command> [options]"
    echo "Available commands:"
    echo "  build                      Build the VCS project"
    echo "  init                       Initialize a new VCS repository"
    echo "  track <file>               Track a file for version control"
    echo "  commit <message>           Commit the current state of tracked files with a message"
    echo "  log                        View the commit history"
    echo "  checkout <commit_id>       Restore the project to a specific commit state"
    exit 1
}


if ! command -v cmake &> /dev/null; then
    echo "Error: CMake is not installed. Please install CMake to continue."
    exit 1
fi

# Check if OpenSSL is installed
if ! command -v openssl &> /dev/null; then
    echo "Error: OpenSSL is not installed. Please install OpenSSL to continue."
    exit 1
fi


if [ "$#" -lt 1 ]; then
    echo "Error: Missing command."
    print_usage
fi

COMMAND=$1


if [ "$COMMAND" == "build" ]; then
    echo "Building the VCS project..."

    # Create the build directory if it doesn't exist
    if [ ! -d "build" ]; then
        mkdir build
    fi

  
    cd build || exit 1

    # Run CMake to configure the project
    cmake .. || { echo "CMake configuration failed."; exit 1; }

    # Run make to build the project
    make || { echo "Build failed."; exit 1; }

    echo "Build successful! Use the following command to run the VCS:"
    echo "./build_and_run_vcs.sh <command> [options]"
    exit 0
fi


if [ ! -f "build/vcs" ]; then
    echo "Error: The VCS project has not been built. Run '$0 build' first."
    exit 1
fi


case "$COMMAND" in
    init)
        ./build/vcs init
        ;;
    track)
        if [ "$#" -ne 2 ]; then
            echo "Error: Missing file argument for track command."
            print_usage
        fi
        ./build/vcs track "$2"
        ;;
    commit)
        if [ "$#" -ne 2 ]; then
            echo "Error: Missing commit message."
            print_usage
        fi
        ./build/vcs commit "$2"
        ;;
    log)
        ./build/vcs log
        ;;
    checkout)
        if [ "$#" -ne 2 ]; then
            echo "Error: Missing commit ID."
            print_usage
        fi
        ./build/vcs checkout "$2"
        ;;
    *)
        echo "Error: Unknown command '$COMMAND'."
        print_usage
        ;;
esac

exit 0
