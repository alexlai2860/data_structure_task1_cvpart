cmake_minimum_required (VERSION 3.1)

project (Map_path_plan)

set (CMAKE_BUILD_TYPE Debug)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory(src SRC_LIST)

include_directories(include)

add_executable(main ${SRC_LIST})

find_package(OpenCV REQUIRED)

INCLUDE_DIRECTORIES({OpenCV_INCLUDE_DIRS})

link_directories(${OpenCV_LIBRARY_DIRS})

target_link_libraries(main ${OpenCV_LIBS})