cmake_minimum_required(VERSION 3.8)
project(summarization VERSION 0.1.0 LANGUAGES C CXX)

# Set C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(sqlite3 URL https://www.sqlite.org/2024/sqlite-amalgamation-3450300.zip)
FetchContent_MakeAvailable(sqlite3)

# Set the path to the SQLite amalgamation directory
set(SQLITE "${CMAKE_SOURCE_DIR}/build/_deps/sqlite3-src")

# Include the SQLite amalgamation directly into the project
add_library(sqlite3 STATIC ${SQLITE}/sqlite3.c)

# Add include directories for SQLite
target_include_directories(sqlite3 PUBLIC ${SQLITE})

# Define the executable and its source files
add_executable(summarization main.cpp database.h)

# Link the SQLite library with our project
target_link_libraries(summarization PRIVATE sqlite3)