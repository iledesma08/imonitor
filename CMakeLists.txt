# CMakeLists.txt

# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.28)

# Set the project name
project(so_i_24_iledesma08 C)

# Set the C standard
set(CMAKE_C_STANDARD 11)

# Set the include directories
include_directories(include)

# Find the required libraries
find_library(PROM_LIB prom REQUIRED)
find_library(PROMHTTP_LIB promhttp REQUIRED)
find_library(MICROHTTPD_LIB microhttpd REQUIRED)

# Add the executable
add_executable(prom-c-client
    include/expose_metrics.h
    include/metrics.h
    src/expose_metrics.c
    src/main.c
    src/metrics.c)

# Link the libraries
target_link_libraries(prom-c-client ${PROM_LIB} ${PROMHTTP_LIB} ${MICROHTTPD_LIB} pthread)
