cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE "C:/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(SDLTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}/${CMAKE_HOST_SYSTEM_NAME})
find_package(SDL2 CONFIG REQUIRED) # you **MUST** have SDL2 installed, no exceptions.
include_directories(${SOURCE_DIR}/include)
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main) #NB: SDL2Main is technically unused as we define SDL_MAIN_HANDLED in main.cpp.