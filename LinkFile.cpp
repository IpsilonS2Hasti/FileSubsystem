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
    FileSystem fs;
    char resolvedPath[256];

    if (content[0] == '/') {
        // Absolute path
        std::strcpy(resolvedPath, content);
    } else {
        // Relative path
        std::strcpy(resolvedPath, getPath());
        char* lastSlash = std::strrchr(resolvedPath, '/');
        if (lastSlash != nullptr) {
            lastSlash[1] = '\0';
        }
        std::strcat(resolvedPath, content);
    }

    FSEntity* targetEntity = fs.findEntityByName(resolvedPath);
    if (targetEntity) {
        File* targetFile = dynamic_cast<File*>(targetEntity);
        if (targetFile) {
            targetFile->execute();
        } else {
            std::cerr << "Target is not an executable file" << std::endl;
        }
    } else {
        std::cerr << "Target file not found: " << resolvedPath << std::endl;
    }
}
