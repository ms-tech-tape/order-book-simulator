cmake_minimum_required(VERSION 3.10)

project(order_book_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    main.cpp
    OrderBook.cpp
)

# Header files
set(HEADERS
    Order.h
    OrderBook.h
    Trade.h
)

# Create executable
add_executable(order_book_simulator ${SOURCES} ${HEADERS})

# Compiler flags
if(MSVC)
    target_compile_options(order_book_simulator PRIVATE /W4)
else()
    target_compile_options(order_book_simulator PRIVATE -Wall -Wextra)
endif()