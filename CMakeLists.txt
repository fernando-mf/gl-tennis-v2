cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Assignment2)

include(ExternalProject)

# Set install directory
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist CACHE PATH ${CMAKE_SOURCE_DIR}/dist FORCE)
set(CMAKE_BUILD_TYPE "Debug")
if(WIN32)
    set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "Debug" FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

include(BuildGLEW)
include(BuildGLFW)
include(BuildGLM)

# a2
set(EXEC a2)

file(GLOB SRC src/*.cpp)
file(GLOB JONATHAN src/JonathanImpl/*.cpp)
file(GLOB FERNANDO src/FernandoImpl/*.cpp)
file(GLOB KIRAN src/KiranImpl/*.cpp)
file(GLOB MATTHEW src/MatthewImpl/*.cpp)

add_executable(${EXEC} ${SRC} ${JONATHAN} ${FERNANDO} ${KIRAN} ${MATTHEW})

target_include_directories(${EXEC} PRIVATE include)

target_link_libraries(${EXEC} OpenGL::GL glew_s glfw glm)

list(APPEND BIN ${EXEC})
# end a2

# install files to install location
install(TARGETS ${BIN} DESTINATION ${CMAKE_INSTALL_PREFIX})

# copy assets
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
        COMMENT "Copying assets to ${CMAKE_CURRENT_BINARY_DIR}/assets")

add_dependencies(${EXEC} copy_assets)