cmake_minimum_required(VERSION 3.16)
project(server)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

include_directories(.)

add_executable(server
        GarbageCollector.cpp
        GarbageCollector.h
        json-forwards.h
        json.h
        jsoncpp.cpp
        List.cpp
        List.h
        main.cpp
        Node.cpp
        Node.h
        server.h
        server.cpp
        hl_exception.h
        hl_hashwrapper.h
        hl_md5.cpp
        hl_md5.h
        hl_md5wrapper.cpp
        hl_md5wrapper.h
        hl_types.h
        )
