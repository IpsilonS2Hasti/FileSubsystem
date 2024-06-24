#pragma once
#include "File.h"

class TextFile : public File {
public:
    TextFile(const char* name, const Date& creationDate, const Date& modificationDate);
    TextFile(const char* name);

    TextFile* clone() const override;
    void execute() const override;
};
