cmake_minimum_required(VERSION 3.4)
project(ComputionalMethodsGUI)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)

# Widgets finds its own dependencies
find_package(Qt5Widgets REQUIRED)

set(SOURCES  sample/main.cpp
     #gui/src/mainwindow.cpp 
     gui/src/matrixinputview.cpp 
     gui/src/mainwindowview.cpp 
     gui/src/control.cpp 
     lib/src/icomputionalmethods.cpp 
     lib/src/gaussmethod.cpp 
     lib/src/kramermethod.cpp 
     lib/src/seidelmethod.cpp 
     lib/src/simpleiterationmethod.cpp 
     lib/src/upperrelaxationmethod.cpp 
     gui/src/qanswerform.cpp 
     gui/src/qinputparamsline.cpp
     gui/src/qinputsizeline.cpp)

set(INCLUDES #gui/include/mainwindow.h 
    gui/include/matrixinputview.h 
    gui/include/mainwindowview.h 
    gui/include/control.h 
    lib/include/icomputionalmethods.h 
    lib/src/gaussmethod.h 
    lib/src/kramermethod.h 
    lib/src/seidelmethod.h 
    lib/src/simpleiterationmethod.h
    lib/src/upperrelaxationmethod.h
    gui/include/qanswerform.h
    gui/include/qinputparamsline.h
    gui/include/qinputsizeline.h)

add_executable(ComputionalMethodsGUI ${SOURCES} ${INCLUDES})
qt5_use_modules(ComputionalMethodsGUI Widgets)
