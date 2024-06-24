#pragma once
#include "Date.h"

class Directory;

class FSEntity{
protected:
    static const int MAX_NAME_LENGTH = 255;

    char name[MAX_NAME_LENGTH + 1] = {};
    Date creationDate;
    Date modificationDate;
    Directory* parentDir = nullptr;

    FSEntity() = default;
    FSEntity(const char* name, const Date& creationDate, const Date& modificationDate, Directory* parentDir);
    FSEntity(const char* name);
public:
    //getters
    const char* getName() const;
    const Date& getCreationDate() const;
    const Date& getModificationDate() const;
    const Directory& getParentDir() const; //should this be const?!

    //setters
    void setName(const char* newName);
    void setModificationDate(const Date& newDate);
    void setParentDir(Directory* newParentDir);

    virtual FSEntity* clone() const = 0;

    virtual ~FSEntity() = default;

    const char* getPath() const;
};