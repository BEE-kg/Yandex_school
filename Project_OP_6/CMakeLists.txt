# Указываем минимальную версию CMake
cmake_minimum_required(VERSION 3.10)

# Указываем название проекта
project(MyProject)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(

    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr
    GIT_TAG 1.10.4
)

FetchContent_MakeAvailable(cpr)

FetchContent_Declare(

    json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(json)

add_executable(MyProject main.cpp parser.cpp all_other_functions.cpp all_important_functions.cpp)
target_link_libraries(MyProject PRIVATE cpr nlohmann_json::nlohmann_json)