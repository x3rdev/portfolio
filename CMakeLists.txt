cmake_minimum_required(VERSION 3.14)
project(portfolio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------
# Fetch ASIO (standalone)
# ---------------------------
include(FetchContent)

FetchContent_Declare(
        asio_src
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG asio-1-36-0
)
FetchContent_MakeAvailable(asio_src)

add_library(asio_headers INTERFACE)
target_include_directories(asio_headers INTERFACE
        ${asio_src_SOURCE_DIR}/asio/include
)
target_compile_definitions(asio_headers INTERFACE
        ASIO_STANDALONE
        ASIO_NO_DEPRECATED
)

# ---------------------------
# Find OpenSSL via vcpkg or system
# ---------------------------
find_package(OpenSSL REQUIRED)

# ---------------------------
# Main executable
# ---------------------------
add_executable(portfolio
        main.cpp
        web_server/web_server.cpp
        indexer/indexer.cpp
        indexer/indexer.h
)

# Include directories
target_include_directories(portfolio PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link libraries
target_link_libraries(portfolio PRIVATE
        asio_headers
        OpenSSL::SSL
        OpenSSL::Crypto
)

# ---------------------------
# Windows-specific
# ---------------------------
if(WIN32)
    target_compile_definitions(portfolio PRIVATE _WIN32_WINNT=0x0A00)
    target_link_libraries(portfolio PRIVATE ws2_32)
endif()