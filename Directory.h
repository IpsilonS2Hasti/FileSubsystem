#pragma once
#include "FSEntity.h"

class Directory : public FSEntity {
public:
    FSEntity** children = nullptr;
    size_t childrenCount = 0;
    size_t capacity = 0;

    void copyFrom(const Directory& other);
    void moveFrom(Directory&& other) noexcept;
    void free();
    void expandCapacity(); // New method to expand capacity
    void remove(size_t index); // New method to remove a child

public:
    Directory(const char* name, const Date& creationDate, const Date& modificaitonDate);
    Directory(const char* name);

    Directory(const Directory& other);
    Directory(Directory&& other) noexcept;

    Directory& operator=(const Directory& other);
    Directory& operator=(Directory&& other) noexcept;

    ~Directory();

    FSEntity* clone() const override;

    void add(FSEntity*&& newEntity);
};
