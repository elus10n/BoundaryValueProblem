cmake_minimum_required(VERSION 3.16)

project(BoundaryValueProblem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

include_directories(include include/Interface include/Kernel include/Solvers)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui

    src/Kernel/functions.cpp
    src/Kernel/integrator.cpp
    src/Kernel/thomas.cpp
    src/Solvers/task1.cpp
    src/Solvers/task2.cpp
    src/Solvers/task4.cpp
    src/Interface/wrapper.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Charts)

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE ON)
endif()
