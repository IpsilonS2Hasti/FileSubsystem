#pragma once
#include "Directory.h"
#include "TextFile.h"
#include "Date.h"

class FileSystem {
private:
    Directory* root;
    Directory* currentDir;

public:
    FileSystem();
    ~FileSystem();

    bool changeDirectory(const char* path);
    void listDirectory(const char* path = nullptr);
    const char* printWorkingDirectory();
    bool makeDirectory(const char* name);
    bool createTextFile(const char* name);
    bool createScriptFile(const char* name);
    bool removeFile(const char* path);
    bool removeDirectory(const char* path);
    void executeFile(const char* path);
    void echo(const char* text, const char* filePath = nullptr, bool append = false);
    FSEntity* findEntityByName(const char* name) const;
};
