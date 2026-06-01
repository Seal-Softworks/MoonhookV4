cmake_minimum_required(VERSION 3.15)
project(MoonhookV4 VERSION 4.0)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDART_REQUIRED True)

include (FetchContent)

FetchContent_Declare(
    luau
    GIT_REPOSITORY https://github.com/luau-lang/luau.git
    GIT_TAG        0.723 
)

set(LUAU_BUILD_CLI OFF CACHE BOOL "" FORCE)
set(LUAU_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(luau)

FetchContent_Declare(
    curl
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG        curl-8_2_0  
)

set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(CURL_DISABLE_TESTS ON CACHE BOOL "" FORCE)
set(BUILD_CURL_EXE OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(curl)

add_executable(moonhookv4
    src/main.cpp
)

target_link_libraries(moonhookv4 PRIVATE
    Luau.VM
    Luau.Compiler
    CURL::libcurl
)

target_include_directories(moonhookv4 PRIVATE
    include/
    ${luau_SOURCE_DIR}/VM/include
    ${luau_SOURCE_DIR}/Compiler/include
)
