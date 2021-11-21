cmake_minimum_required(VERSION 3.18)

project(NotChess)

find_package(SFML COMPONENTS system window graphics REQUIRED)
add_subdirectory(src)
