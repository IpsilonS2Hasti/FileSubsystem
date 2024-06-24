#include "FSEntity.h"
#include "Directory.h"
#include <cstring>

FSEntity::FSEntity(const char* name, const Date& creationDate, const Date& modificationDate, Directory* parentDir)
    : creationDate(creationDate), modificationDate(modificationDate), parentDir(parentDir) {
    setName(name);
}

FSEntity::FSEntity(const char *name) {
    setName(name);
}

//getters
const char* FSEntity::getName() const{
    return name;
}

const Date& FSEntity::getCreationDate() const {
    return creationDate;
}

const Date& FSEntity::getModificationDate() const {
    return modificationDate;
}

const Directory& FSEntity::getParentDir() const {
    return *parentDir;
}

//setters
void FSEntity::setName(const char *newName) {
    if (newName != nullptr) {
        strcpy(name, newName);
        name[MAX_NAME_LENGTH] = '\0';
    }
}

void FSEntity::setModificationDate(const Date &newDate) {
    creationDate = newDate; //trivially copyable
}

void FSEntity::setParentDir(Directory *newParentDir) {
    parentDir = newParentDir;
}

const char* FSEntity::getPath() const {
    static char fullPath[MAX_NAME_LENGTH * 10]; //should be enough for most path, realistically
    char tempPath[MAX_NAME_LENGTH * 10];
    char* tempPtr = tempPath + sizeof(tempPath) - 1;
    *tempPtr = '\0';

    const FSEntity* current = this;
    while (current != nullptr) {
        const char* currentName = current->getName();
        size_t nameLength = 0;

        while (currentName[nameLength] != '\0') {
            ++nameLength;
        }

        if (tempPtr - nameLength - 1 < tempPath) {
            break;
        }

        tempPtr -= nameLength;
        for (size_t i = 0; i < nameLength; ++i) {
            tempPtr[i] = currentName[i];
        }

        if (&(current->getParentDir()) != nullptr) {
            --tempPtr;
            *tempPtr = '/';
        }

        current = &(current->getParentDir());
    }

    char* fullPathPtr = fullPath;
    while (*tempPtr != '\0') {
        *fullPathPtr++ = *tempPtr++;
    }
    *fullPathPtr = '\0';

    return fullPath;
}

