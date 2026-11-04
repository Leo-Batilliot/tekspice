cmake_minimum_required(VERSION 3.20)

project(nanotekspice VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-W -Wall -Wextra -Werror)

add_executable(nanotekspice
  src/main.cpp
  src/Factory/Factory.cpp
  src/Utils/Parsing.cpp
  src/Utils/Sim.cpp
  include/AComponent.cpp
  ## COMPONENTS
  # SPECIAL
  src/Components/Special/Input.cpp
  src/Components/Special/Output.cpp
  src/Components/Special/True.cpp
  src/Components/Special/False.cpp
  src/Components/Special/Clock.cpp
  src/Components/Special/Logger.cpp
  # ELEMENTARY
  src/Components/Elementary/And.cpp
  src/Components/Elementary/Not.cpp
  src/Components/Elementary/Or.cpp
  src/Components/Elementary/Xor.cpp
  # GATES
  src/Components/Gates/4001.cpp
  src/Components/Gates/4011.cpp
  src/Components/Gates/4030.cpp
  src/Components/Gates/4069.cpp
  src/Components/Gates/4071.cpp
  src/Components/Gates/4081.cpp
  # ADVANCED
  src/Components/Advanced/4008.cpp
  src/Components/Advanced/4512.cpp
  src/Components/Advanced/4040.cpp
  src/Components/Advanced/4017.cpp
  src/Components/Advanced/4514.cpp
  src/Components/Advanced/2716.cpp
  src/Components/Advanced/4013.cpp
  src/Components/Advanced/4094.cpp
  src/Components/Advanced/4801.cpp

)

include_directories(.)
include_directories(src)
include_directories(include)
include_directories(src/Components)
include_directories(src/Components/Advanced)
include_directories(src/Components/Elementary)
include_directories(src/Components/Gates)
include_directories(src/Components/Special)
include_directories(src/Factory)
include_directories(src/Utils)
