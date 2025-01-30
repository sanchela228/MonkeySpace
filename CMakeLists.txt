cmake_minimum_required(VERSION 3.30)
project(MonkeySpace)

include_directories(include)

set(CMAKE_CXX_STANDARD 26)

set(SOURCES
    source/main.cpp
        source/types/Vector3.cpp
        source/utils/Random.cpp
        include/utils/Random.h
        source/types/Quaternion.cpp
        include/types/Quaternion.h
        include/types/Vector3.h
)

add_executable(MonkeySpace ${SOURCES})
