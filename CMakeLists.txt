cmake_minimum_required(VERSION 3.16)

project(BoundaryValueProblem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(
    include
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    include/Interface/wrapper.h
    include/Kernel/functions.h
    include/Kernel/integrator.h
    include/Kernel/thomas.h
    include/Solvers/solver_wrappers.h
    include/Solvers/task1.h
    include/Solvers/task4.h
    src/mainwindow.h src/mainwindow.cpp src/mainwindow.ui
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE ON)
endif()
