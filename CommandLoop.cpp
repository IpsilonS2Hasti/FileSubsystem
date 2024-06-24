#include "CommandLoop.h"
#include <cstring>
#include <iostream>

void CommandLoop::processCommand(const char* command) {
    char buffer[256];
    std::strncpy(buffer, command, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char* cmd = std::strtok(buffer, " ");
    if (cmd == nullptr) {
        std::cerr << "Invalid command" << std::endl;
        return;
    }

    if (std::strcmp(cmd, "cd") == 0) {
        char* path = std::strtok(nullptr, " ");
        if (path) {
            if (!fileSystem.changeDirectory(path)) {
                std::cerr << "Invalid path" << std::endl;
            }
        } else {
            std::cerr << "Usage: cd <path>" << std::endl;
        }
    } else if (std::strcmp(cmd, "ls") == 0) {
        char* path = std::strtok(nullptr, " ");
        fileSystem.listDirectory(path);
    } else if (std::strcmp(cmd, "pwd") == 0) {
        std::cout << fileSystem.printWorkingDirectory() << std::endl;
    } else if (std::strcmp(cmd, "mkdir") == 0) {
        char* name = std::strtok(nullptr, " ");
        if (name) {
            if (!fileSystem.makeDirectory(name)) {
                std::cerr << "Directory creation failed" << std::endl;
            }
        } else {
            std::cerr << "Usage: mkdir <directory name>" << std::endl;
        }
    } else if (std::strcmp(cmd, "touch") == 0) {
        char* name = std::strtok(nullptr, " ");
        if (name) {
            if (std::strstr(name, ".sh") != nullptr) {
                if (!fileSystem.createScriptFile(name)) {
                    std::cerr << "Script file creation failed" << std::endl;
                }
            } else {
                if (!fileSystem.createTextFile(name)) {
                    std::cerr << "File creation failed" << std::endl;
                }
            }
        } else {
            std::cerr << "Usage: touch <file name>" << std::endl;
        }
    } else if (std::strcmp(cmd, "rm") == 0) {
        char* path = std::strtok(nullptr, " ");
        if (path) {
            if (!fileSystem.removeFile(path)) {
                std::cerr << "File removal failed" << std::endl;
            }
        } else {
            std::cerr << "Usage: rm <file path>" << std::endl;
        }
    } else if (std::strcmp(cmd, "rmdir") == 0) {
        char* path = std::strtok(nullptr, " ");
        if (path) {
            if (!fileSystem.removeDirectory(path)) {
                std::cerr << "Directory removal failed" << std::endl;
            }
        } else {
            std::cerr << "Usage: rmdir <directory path>" << std::endl;
        }
    } else if (std::strcmp(cmd, "exec") == 0) {
        char* path = std::strtok(nullptr, " ");
        if (path) {
            fileSystem.executeFile(path);
        } else {
            std::cerr << "Usage: exec <file path>" << std::endl;
        }
    } else if (std::strcmp(cmd, "echo") == 0) {
        char* text = std::strtok(nullptr, "");
        if (text) {
            char* op = std::strstr(text, " > ");
            bool append = false;
            if (!op) {
                op = std::strstr(text, " >> ");
                append = true;
            }

            if (op) {
                *op = '\0'; // Split the string at the operator
                op += append ? 4 : 3; // Move past the operator

                // Trim leading spaces from the file path
                while (*op == ' ') op++;

                if (*op) {
                    fileSystem.echo(text, op, append);
                } else {
                    std::cerr << "Usage: echo <text> [> <file> | >> <file>]" << std::endl;
                }
            } else {
                fileSystem.echo(text);
            }
        } else {
            std::cerr << "Usage: echo <text> [> <file> | >> <file>]" << std::endl;
        }
    } else if (std::strcmp(cmd, "exit") == 0) {
        std::cout << "Exiting..." << std::endl;
        exit(0);
    } else {
        std::cerr << "Unknown command: " << cmd << std::endl;
    }
}

void CommandLoop::run() {
    char line[256];
    while (true) {
        std::cout << "> ";
        if (!std::cin.getline(line, sizeof(line))) {
            break;
        }
        processCommand(line);
    }
}
