#include "LinkFile.h"
#include "FileSystem.h"
#include <cstring>
#include <iostream>

LinkFile::LinkFile(const char* name, const Date& creationDate, const Date& modificationDate)
        : File(name, creationDate, modificationDate) {
}

LinkFile::LinkFile(const char* name)
        : File(name) {
}

LinkFile* LinkFile::clone() const {
    return new LinkFile(*this);
}

void LinkFile::execute() const {
    if (std::strlen(content) == 0) {
        std::cerr << "Link target is empty" << std::endl;
        return;
    }

    char command[256];
    std::strcpy(command, "exec ");
    std::strcat(command, content);

    int result = system(command);
    if (result == -1) {
        std::cerr << "Failed to execute command: " << command << std::endl;
    }
}
