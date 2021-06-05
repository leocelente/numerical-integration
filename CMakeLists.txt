cmake_minimum_required(VERSION 3.12)
project(MyProject)

# Language Server (compile_commands.json)
# ln -s build/compile_commands.json ./compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Conan 
add_definitions("-std=c++20")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Main Project
add_executable(my_project src/main.cpp src/module.cpp)
target_link_libraries(my_project ${CONAN_LIBS})
target_include_directories(my_project PRIVATE "inc")

# Main Tests
add_executable(my_project-tests tests/catch.cpp src/module.cpp tests/tests.cpp)
target_link_libraries(my_project-tests ${CONAN_LIBS})
target_include_directories(my_project-tests PRIVATE "inc")

enable_testing()
add_test(NAME "MyProject-Tests" COMMAND my_project-tests)
