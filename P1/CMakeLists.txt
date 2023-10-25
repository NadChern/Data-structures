cmake_minimum_required(VERSION 3.26)
project(p1)

set(CMAKE_CXX_STANDARD 17)

add_executable(p1 p1.cpp
        BookList.cpp BookList.h
        MemberList.h
        MemberList.cpp
        RatingList.h
        RatingList.cpp)
