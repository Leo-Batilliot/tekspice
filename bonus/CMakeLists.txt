cmake_minimum_required(VERSION 3.20)

project(NanoBonus)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(SFML)

add_compile_options(-W -Wall -Wextra -Werror)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Core/Component.cpp
    src/Core/Circuit.cpp
    src/Core/Camera.cpp
    src/Core/Toolbar.cpp
    src/Components/AndGate.cpp
    src/Components/OrGate.cpp
    src/Components/NotGate.cpp
    src/Components/Input.cpp
    src/Components/Output.cpp
    src/Components/TrueInput.cpp
    src/Components/FalseInput.cpp
)

include_directories(src)
include_directories(src/Core)
include_directories(src/Components)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)