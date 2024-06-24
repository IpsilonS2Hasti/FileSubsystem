#pragma once
#include "File.h"

class LinkFile : public File {
public:
    LinkFile(const char* name, const Date& creationDate, const Date& modificationDate);
    LinkFile(const char* name);

    LinkFile* clone() const override;
    void execute() const override;
};
