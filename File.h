#pragma once
#include "FSEntity.h"

class File : public FSEntity {
protected:
    char* content;

    void copyFrom(const File& other);
    void moveFrom(File&& other) noexcept;
    void free();

public:
    File(const char* name, const Date& creationDate, const Date& modificationDate);
    File(const char* name);

    File(const File& other);
    File(File&& other) noexcept;

    File& operator=(const File& other);
    File& operator=(File&& other) noexcept;

    virtual ~File();

    void setContent(const char* newContent);
    const char* getContent() const;

    virtual void execute() const = 0;
};
