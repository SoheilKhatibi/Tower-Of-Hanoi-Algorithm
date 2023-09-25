cmake_minimum_required(VERSION 3.10)
project(tower_of_hanoi)
set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SOURCE_FILES main.cpp ring.cpp tower.cpp)

add_executable(tower_of_hanoi ${SOURCE_FILES})
target_link_libraries(tower_of_hanoi ${OpenCV_LIBS})
