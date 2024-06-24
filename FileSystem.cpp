#include "FileSystem.h"
#include "ScriptFile.h"
#include <iostream>
#include <cstring>

FileSystem::FileSystem() {
    Date currentDate;
    root = new Directory("root", currentDate, currentDate);
    currentDir = root;
}

FileSystem::~FileSystem() {
    delete root;
}

bool FileSystem::changeDirectory(const char* path) {
    Directory* startingDir = currentDir;

    if (path[0] == '/') { //Absolute paths begin with /, without writing root!
        currentDir = root;
        path++; // Move past the '/'
    }

    char buffer[256];
    std::strncpy(buffer, path, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char* token = std::strtok(buffer, "/");
    while (token != nullptr) {
        if (std::strcmp(token, "..") == 0) {
            if (&(currentDir->getParentDir()) != nullptr) {
                currentDir = const_cast<Directory*>(&currentDir->getParentDir());
            }
        } else {
            bool found = false;
            for (size_t i = 0; i < currentDir->childrenCount; ++i) {
                Directory* dir = dynamic_cast<Directory*>(currentDir->children[i]);
                if (dir && std::strcmp(dir->getName(), token) == 0) {
                    currentDir = dir;
                    found = true;
                    break;
                }
            }
            if (!found) {
                std::cerr << "Directory not found: " << token << std::endl;
                currentDir = startingDir;
                return false;
            }
        }
        token = std::strtok(nullptr, "/");
    }
    return true;
}

void FileSystem::listDirectory(const char* path) {
    Directory* dir = currentDir;
    if (path) {
        if (!changeDirectory(path)) {
            std::cerr << "Directory not found" << std::endl;
            return;
        }
        dir = currentDir;
    }

    for (size_t i = 0; i < dir->childrenCount; ++i) {
        std::cout << dir->children[i]->getName() << " ";
        std::cout << "Created: " << dir->children[i]->getCreationDate() << " ";
        std::cout << "Modified: " << dir->children[i]->getModificationDate() << std::endl;
    }

    if (path) {
        changeDirectory("..");
    }
}

const char* FileSystem::printWorkingDirectory() {
    return currentDir->getPath();
}

bool FileSystem::makeDirectory(const char* name) {
    for (size_t i = 0; i < currentDir->childrenCount; ++i) {
        if (std::strcmp(currentDir->children[i]->getName(), name) == 0) {
            std::cerr << "Directory or file already exists" << std::endl;
            return false;
        }
    }
    Date currentDate;
    Directory* newDir = new Directory(name, currentDate, currentDate);
    currentDir->add(newDir);
    return true;
}

bool FileSystem::createTextFile(const char* name) {
    for (size_t i = 0; i < currentDir->childrenCount; ++i) {
        if (std::strcmp(currentDir->children[i]->getName(), name) == 0) {
            currentDir->children[i]->setModificationDate(Date());
            return true;
        }
    }

    Date currentDate;
    TextFile* newFile = new TextFile(name, currentDate, currentDate);
    currentDir->add(newFile);
    return true;
}

bool FileSystem::createScriptFile(const char* name) {
    for (size_t i = 0; i < currentDir->childrenCount; ++i) {
        if (std::strcmp(currentDir->children[i]->getName(), name) == 0) {
            currentDir->children[i]->setModificationDate(Date());
            return true;
        }
    }

    Date currentDate;
    ScriptFile* newFile = new ScriptFile(name, currentDate, currentDate);
    currentDir->add(newFile);
    return true;
}

bool FileSystem::removeFile(const char* path) {
    for (size_t i = 0; i < currentDir->childrenCount; ++i) {
        if (std::strcmp(currentDir->children[i]->getName(), path) == 0) {
            delete currentDir->children[i];
            for (size_t j = i; j < currentDir->childrenCount - 1; ++j) {
                currentDir->children[j] = currentDir->children[j + 1];
            }
            currentDir->childrenCount--;
            return true;
        }
    }
    std::cerr << "File not found" << std::endl;
    return false;
}

bool FileSystem::removeDirectory(const char* path) {
    for (size_t i = 0; i < currentDir->childrenCount; ++i) {
        Directory* dir = dynamic_cast<Directory*>(currentDir->children[i]);
        if (dir && std::strcmp(dir->getName(), path) == 0) {
            if (dir->childrenCount > 0) {
                std::cerr << "Directory not empty" << std::endl;
                return false;
            }
            delete currentDir->children[i];
            for (size_t j = i; j < currentDir->childrenCount - 1; ++j) {
                currentDir->children[j] = currentDir->children[j + 1];
            }
            currentDir->childrenCount--;
            return true;
        }
    }
    std::cerr << "Directory not found" << std::endl;
    return false;
}

void FileSystem::executeFile(const char* path) {
    for (size_t i = 0; i < currentDir->childrenCount; ++i) {
        File* file = dynamic_cast<File*>(currentDir->children[i]);
        if (file && std::strcmp(file->getName(), path) == 0) {
            file->execute();
            return;
        }
    }
    std::cerr << "File not found or not executable" << std::endl;
}

void FileSystem::echo(const char* text, const char* filePath, bool append) {
    if (!filePath) {
        std::cout << text << std::endl;
        return;
    }

    FSEntity* entity = findEntityByName(filePath);
    if (entity == nullptr) {
        std::cerr << "File not found" << std::endl;
        return;
    }

    File* file = dynamic_cast<File*>(entity);
    if (file) {
        const char* currentContent = file->getContent() == nullptr ? "" : file->getContent();

        size_t currentContentLength = std::strlen(currentContent);
        size_t newTextLength = std::strlen(text);
        size_t newContentLength = append ? (currentContentLength + newTextLength + 2) : (newTextLength + 1);

        char* newContent = new char[newContentLength];
        if (append) {
            std::strcpy(newContent, currentContent);
            std::strcat(newContent, "\n");
            std::strcat(newContent, text);
        } else {
            std::strcpy(newContent, text);
        }

        file->setContent(newContent);
        delete[] newContent;
    } else {
        std::cerr << "Echo operation is only supported for TextFile and ScriptFile" << std::endl;
    }
}


FSEntity* FileSystem::findEntityByName(const char* name) const {
    for (size_t i = 0; i < currentDir->childrenCount; ++i) {
        if (std::strcmp(currentDir->children[i]->getName(), name) == 0) {
            return currentDir->children[i];
        }
    }
    return nullptr;
}