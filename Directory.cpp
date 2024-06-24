#include "Directory.h"
#include <iostream>
#include <cstring>

FSEntity* Directory::clone() const {
    return new Directory(*this);
}

void Directory::copyFrom(const Directory &other) {
    children = new FSEntity*[other.capacity];
    for(size_t i = 0; i < other.childrenCount; i++){
        children[i] = other.children[i]->clone();
    }
    childrenCount = other.childrenCount;
    capacity = other.capacity;
}

void Directory::moveFrom(Directory &&other) noexcept {
    children = other.children;
    childrenCount = other.childrenCount;
    capacity = other.capacity;

    other.children = nullptr;
    other.childrenCount = 0;
    other.capacity = 0;
}

void Directory::free() {
    for (size_t i = 0; i < childrenCount; i++){
        delete children[i];
    }
    delete[] children;
    children = nullptr;

    childrenCount = 0;
    capacity = 0;
}

Directory::Directory(const char* name, const Date& creationDate, const Date& modificaitonDate)
        : FSEntity(name, creationDate, modificaitonDate, nullptr) {
    capacity = 8;
    children = new FSEntity*[capacity];
}

Directory::Directory(const char* name)
        : FSEntity(name) {
    capacity = 8;
    children = new FSEntity*[capacity];
}

void Directory::add(FSEntity*&& newEntity) {
    newEntity->setParentDir(this);
    if (childrenCount >= capacity) {
        expandCapacity();
    }
    children[childrenCount++] = newEntity;
}

void Directory::expandCapacity() {
    size_t newCapacity = capacity * 2;
    FSEntity** newChildren = new FSEntity*[newCapacity];
    for (size_t i = 0; i < childrenCount; ++i) {
        newChildren[i] = children[i];
    }
    delete[] children;
    children = newChildren;
    capacity = newCapacity;
}

void Directory::remove(size_t index) {
    if (index < childrenCount) {
        delete children[index];
        for (size_t i = index; i < childrenCount - 1; ++i) {
            children[i] = children[i + 1];
        }
        --childrenCount;
    }
}

Directory::Directory(const Directory &other) : FSEntity(other) {
    copyFrom(other);
}

Directory::Directory(Directory&& other) noexcept : FSEntity(std::move(other)) {
    moveFrom(std::move(other));
}

Directory& Directory::operator=(const Directory& other) {
    if(this != &other) {
        FSEntity::operator=(other);
        free();
        copyFrom(other);
    }
    return *this;
}

Directory& Directory::operator=(Directory&& other) noexcept {
    if(this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Directory::~Directory() {
    free();
}
