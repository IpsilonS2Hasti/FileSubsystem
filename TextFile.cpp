#include "TextFile.h"
#include <iostream>

TextFile::TextFile(const char* name, const Date& creationDate, const Date& modificationDate)
        : File(name, creationDate, modificationDate) {}

TextFile::TextFile(const char* name)
        : File(name) {}

TextFile *TextFile::clone() const {
    return new TextFile(*this);
}

void TextFile::execute() const {
    std::cout << "Reading file: " << name << std::endl;
    std::cout << "Content: " << std::endl << (content ? content : "No content") << std::endl;
}
