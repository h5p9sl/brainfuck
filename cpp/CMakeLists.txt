cmake_minimum_required(VERSION 3.0)

project(brainfuck)

file(GLOB SOURCES
    "src/*.cpp"
)

add_executable(brainfuck ${SOURCES})
