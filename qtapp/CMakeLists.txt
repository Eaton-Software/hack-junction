cmake_minimum_required(VERSION 2.8.11)

project(qtapp)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(OpenCV REQUIRED)

# Tell CMake to create the helloworld executable
add_executable(qtapp main.cpp mainwindow.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(qtapp Qt5::Widgets)

find_package(Qt5Core)

add_subdirectory(cpr)

target_link_libraries(qtapp ${CPR_LIBRARIES} ${OpenCV_LIBS})
include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})
