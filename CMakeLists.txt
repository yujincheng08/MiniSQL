
 cmake_minimum_required(VERSION 3.7)
 project(MiniSQL)

 set(CMAKE_CXX_STANDARD 11)

 file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.hpp" "*.h" "*.c")

 add_executable(MiniSQL ${SOURCE_FILES})