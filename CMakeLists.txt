cmake_minimum_required(VERSION 3.19)
project(openglplayground CXX)

find_program(CONAN_EXECUTABLE conan
    DOC "Path to Conan Package Manager")
mark_as_advanced(CONAN_EXECUTABLE)

if (NOT CONAN_EXECUTABLE)
message(FATAL_ERROR "Can't find conan executable!")
endif()

set(CONAN_FILES_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/.conan")
# Clean old conan ouptut files first
execute_process(COMMAND "${CMAKE_COMMAND}" -E remove_directory "${CONAN_FILES_OUTPUT_DIR}")
execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${CONAN_FILES_OUTPUT_DIR}")

execute_process(COMMAND "${CONAN_EXECUTABLE}" install ${PROJECT_SOURCE_DIR} --build=missing -s build_type=RelWithDebInfo WORKING_DIRECTORY "${CONAN_FILES_OUTPUT_DIR}")
execute_process(COMMAND "${CONAN_EXECUTABLE}" install ${PROJECT_SOURCE_DIR} --build=missing -s build_type=Debug WORKING_DIRECTORY "${CONAN_FILES_OUTPUT_DIR}")

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)
set(CMAKE_FIND_ROOT_PATH ${CMAKE_FIND_ROOT_PATH} "${CONAN_FILES_OUTPUT_DIR}")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CONAN_FILES_OUTPUT_DIR}")
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

add_executable(${PROJECT_NAME})
target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_20)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        "${CMAKE_SOURCE_DIR}/include"
        
    PRIVATE
        "${CMAKE_SOURCE_DIR}/src"        
        )
target_link_libraries(${PROJECT_NAME} PRIVATE glfw::glfw glad::glad)

target_sources(${PROJECT_NAME}
    PUBLIC

    PRIVATE
        "include/stb_image.h"
        "include/utils.h"
        "src/main.cpp"
        "src/stb_image.cpp"
        "src/HelloTriangles/HelloTriangles.h"
        "src/HelloTriangles/HelloTriangles.cpp" "src/utils.cpp")

add_custom_target(copy_shader_files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/src/shader"
    "${CMAKE_BINARY_DIR}/shader"
)

