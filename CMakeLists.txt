cmake_minimum_required(VERSION 3.26)
project(TR3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Q12 main.cpp
        data_structures_library.cpp
        Question_2.cpp) # testing q2 which contains q1


add_executable(Q3 main2.cpp
        data_structures_library.cpp
        Question_3.cpp) # testing q3
