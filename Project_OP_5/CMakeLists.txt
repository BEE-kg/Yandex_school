# Указываем минимальную версию CMake
cmake_minimum_required(VERSION 3.10)

# Указываем название проекта
project(MyProject)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем исходные файлы
add_executable(a.exe
    main.cpp
    all_other_functions.cpp
    parser.cpp
    important_functions.cpp
    work_with_file.cpp
)
