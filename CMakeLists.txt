cmake_minimum_required(VERSION 3.16)
project(vcalc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(CRYPTOPP_LIB cryptopp)
if(NOT CRYPTOPP_LIB)
    message(FATAL_ERROR "Crypto++ library not found. Install libcrypto++-dev.")
endif()

add_executable(vcalc
    src/main.cpp
    src/CommandLineInterface.cpp
    src/Server.cpp
    src/Auth.cpp
    src/Calculator.cpp
    src/Logger.cpp
    src/Vector.cpp
)

target_include_directories(vcalc PRIVATE include)
target_link_libraries(vcalc PRIVATE ${CRYPTOPP_LIB})
