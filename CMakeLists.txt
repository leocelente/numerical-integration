cmake_minimum_required(VERSION 3.12)
project(MyProject)

# Language Server (compile_commands.json)
# ln -s build/compile_commands.json ./compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(TBB REQUIRED)

# Conan
add_definitions("-std=c++2a")
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake"
    EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
    TLS_VERIFY ON)
endif()


include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE ${CMAKE_SOURCE_DIR}
  BUILD missing
  REMOTE conan-center
  SETTINGS ${settings})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
# Main Project
add_executable(my_project src/main.cpp)
target_link_libraries(my_project ${CONAN_LIBS} ${TBB_IMPORTED_TARGETS})
target_include_directories(my_project PRIVATE "inc")
# Main Tests
add_executable(my_project-tests tests/catch.cpp tests/tests.cpp)
target_link_libraries(my_project-tests ${CONAN_LIBS} ${TBB_IMPORTED_TARGETS})
target_include_directories(my_project-tests PRIVATE "inc")

enable_testing()
add_test(NAME "MyProject-Tests" COMMAND my_project-tests)
