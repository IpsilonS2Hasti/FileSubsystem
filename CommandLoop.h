#pragma once
#include "FileSystem.h"

class CommandLoop {
private:
    FileSystem fileSystem;

public:
    void run();

    void processCommand(const char* command);
};
