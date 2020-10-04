cmake_minimum_required(VERSION 3.17)
project(Resizable_Table)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -municode")
set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lgdiplus")

add_executable(Resizable_Table main.cpp TableDrawer/TableDrawer.h TableDrawer/TableCell.h)