#include "ScriptFile.h"
#include "CommandLoop.h"
#include <cstring>
#include <iostream>

ScriptFile::ScriptFile(const char* name, const Date& creationDate, const Date& modificationDate)
        : File(name, creationDate, modificationDate) {}

ScriptFile::ScriptFile(const char* name)
        : File(name) {}

void ScriptFile::execute() const {
    char* commandBuffer = new char[std::strlen(content) + 1];
    std::strcpy(commandBuffer, content);

    CommandLoop commandLoop;  // Create an instance of CommandLoop

    char* command = std::strtok(commandBuffer, "\n");
    while (command != nullptr) {
        commandLoop.processCommand(command);
        command = std::strtok(nullptr, "\n");
    }

    delete[] commandBuffer;
}

FSEntity* ScriptFile::clone() const {
    return new ScriptFile(*this);
}
