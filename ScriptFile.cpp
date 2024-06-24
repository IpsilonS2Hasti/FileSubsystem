#include "ScriptFile.h"
#include "CommandLoop.h"
#include <cstring>
#include <iostream>

ScriptFile::ScriptFile(const char* name, const Date& creationDate, const Date& modificationDate)
        : File(name, creationDate, modificationDate) {
    content = new char[1];
    content[0] = '\0';
}

ScriptFile::ScriptFile(const char* name)
        : File(name) {
    content = new char[1];
    content[0] = '\0';
}

void ScriptFile::setContent(const char* newContent) {
    delete[] content;
    size_t length = 0;
    while (newContent[length] != '\0') {
        ++length;
    }
    content = new char[length + 1];
    for (size_t i = 0; i <= length; ++i) {
        content[i] = newContent[i];
    }
}

const char* ScriptFile::getContent() const {
    return content;
}

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
