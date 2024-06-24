#pragma once
#include "File.h"

class ScriptFile : public File {
public:
    ScriptFile(const char* name, const Date& creationDate, const Date& modificationDate);
    ScriptFile(const char* name);

    void execute() const override;
    FSEntity* clone() const override;
};
