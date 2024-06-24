cmake_minimum_required(VERSION 3.26)
project(FileSubsystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(FileSubsystem main.cpp
        Date.cpp
        Date.h
        FSEntity.cpp
        FSEntity.h
        Directory.cpp
        Directory.h
        File.cpp
        File.h
        TextFile.cpp
        TextFile.h
        FileSystem.cpp
        FileSystem.h
        CommandLoop.cpp
        CommandLoop.h
        ScriptFile.cpp
        ScriptFile.h
)
