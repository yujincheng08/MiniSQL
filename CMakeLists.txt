
 cmake_minimum_required(VERSION 3.7)
 project(MiniSQL)

 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}
    ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
 set(CMAKE_CXX_STANDARD 11)
 set(CMAKE_AUTOMOC ON)
 set(CMAKE_AUTOUIC ON)
 set(CMAKE_INCLUDE_CURRENT_DIR ON)

 file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.hpp" "*.h" "*.c")
 find_package(Qt5 COMPONENTS Core REQUIRED)

 add_executable(MiniSQL ${SOURCE_FILES})

 target_link_libraries(MiniSQL Qt5::Core)