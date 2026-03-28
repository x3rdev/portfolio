cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0135 NEW)
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

# Fetch google test
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests
        test/JsonBooleanTest.cpp
        test/JsonNumberTest.cpp
        test/JsonStringTest.cpp
)

target_include_directories(tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/indexer/json/JsonElement.h
        src/indexer/json/JsonBoolean.cpp
        src/indexer/json/JsonNumber.cpp
        src/indexer/json/JsonString.cpp
)

target_link_libraries(tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

# ---------------------------
# Find OpenSSL via vcpkg or system
# ---------------------------
find_package(OpenSSL REQUIRED)

# ---------------------------
# Main executable
# ---------------------------
add_executable(portfolio
        src/main.cpp
        src/web_server/web_server.cpp
        src/indexer/indexer.cpp
        src/indexer/indexer.h
        src/indexer/json/JsonElement.h
        src/indexer/json/JsonBoolean.cpp
        src/indexer/json/JsonBoolean.h
        src/indexer/json/JsonNumber.cpp
        src/indexer/json/JsonNumber.h
        src/indexer/json/JsonString.cpp
        src/indexer/json/JsonString.h
        src/indexer/json/JsonObject.cpp
        src/indexer/json/JsonObject.h
        src/indexer/json/JsonArray.cpp
        src/indexer/json/JsonArray.h
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