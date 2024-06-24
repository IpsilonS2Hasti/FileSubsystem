#include "File.h"
#include <cstring>
#include <iostream>

File::File(const char* name, const Date& creationDate, const Date& modificationDate)
        : FSEntity(name, creationDate, modificationDate, nullptr), content(nullptr) {}

File::File(const char* name)
        : FSEntity(name), content(nullptr) {}

File::File(const File& other) : FSEntity(other) {
    copyFrom(other);
}

File::File(File&& other) noexcept : FSEntity(std::move(other)) {
    moveFrom(std::move(other));
}

File::~File() {
    free();
}

File& File::operator=(const File& other) {
    if (this != &other) {
        FSEntity::operator=(other);
        free();
        copyFrom(other);
    }
    return *this;
}

File& File::operator=(File&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

void File::setContent(const char* newContent) {
    if (content) {
        delete[] content;
    }
    content = new char[std::strlen(newContent) + 1];
    std::strcpy(content, newContent);
}

const char* File::getContent() const {
    return content;
}

void File::free() {
    delete[] content;
    content = nullptr;
}

void File::copyFrom(const File& other) {
    setContent(other.content);
}

void File::moveFrom(File&& other) noexcept {
    content = other.content;
    other.content = nullptr;
}
