cmake_minimum_required(VERSION 3.17)
project(tekspice_tests LANGUAGES C CXX)

include(CTest)
enable_testing()

# ACTIVE THE MODULE WHO PERMITTED TO CMAKE TO DL A LIB EXTERN
include(FetchContent)

# FETCH CONTENT OF GOOGLE TEST
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# ACTIVE CTEST
FetchContent_MakeAvailable(googletest)

# ENABLE TEST
enable_testing()

# ADD EXECUTABLE
add_executable(unit_tests
  ../src/Factory/Factory.cpp
  ../src/Utils/Parsing.cpp
  ../src/Utils/Sim.cpp
  ../include/AComponent.cpp

  # TEST
  Components/Special/Input.cpp
  Components/Special/Output.cpp
  Components/Special/True.cpp
  Components/Special/False.cpp
  Components/Special/Clock.cpp
  Components/Special/Logger.cpp
  # ELEMENTARY
  Components/Elementary/And.cpp
  Components/Elementary/Or.cpp
  Components/Elementary/Not.cpp
  Components/Elementary/Xor.cpp
  # GATES
  Components/Gates/4001.cpp
  Components/Gates/4011.cpp
  Components/Gates/4030.cpp
  Components/Gates/4069.cpp
  Components/Gates/4071.cpp
  Components/Gates/4081.cpp
  # ADVANCED
  Components/Advanced/4008.cpp
  Components/Advanced/4512.cpp
  Components/Advanced/4040.cpp
  Components/Advanced/4017.cpp
  # FACTORY
  Factory/Factory.cpp
  # UTILS
  Utils/Parsing.cpp

  ## COMPONENTS
  # SPECIAL
  ../src/Components/Special/Input.cpp
  ../src/Components/Special/Output.cpp
  ../src/Components/Special/True.cpp
  ../src/Components/Special/False.cpp
  ../src/Components/Special/Clock.cpp
  ../src/Components/Special/Logger.cpp
  # ELEMENTARY
  ../src/Components/Elementary/And.cpp
  ../src/Components/Elementary/Not.cpp
  ../src/Components/Elementary/Or.cpp
  ../src/Components/Elementary/Xor.cpp
  # GATES
  ../src/Components/Gates/4001.cpp
  ../src/Components/Gates/4011.cpp
  ../src/Components/Gates/4030.cpp
  ../src/Components/Gates/4069.cpp
  ../src/Components/Gates/4071.cpp
  ../src/Components/Gates/4081.cpp
  # ADVANCED
  ../src/Components/Advanced/4008.cpp
  ../src/Components/Advanced/4512.cpp
  ../src/Components/Advanced/4040.cpp
  ../src/Components/Advanced/4017.cpp
  ../src/Components/Advanced/4514.cpp
  ../src/Components/Advanced/2716.cpp
  ../src/Components/Advanced/4013.cpp
  ../src/Components/Advanced/4094.cpp
  ../src/Components/Advanced/4801.cpp

  # FACTORT
  ../src/Factory/Factory.cpp
  ../src/Utils/Parsing.cpp
)

target_include_directories(unit_tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${CMAKE_CURRENT_SOURCE_DIR}/../src
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/Components
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/Components/Advanced
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/Components/Elementary
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/Components/Gates
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/Components/Special
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/Factory
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/Utils
)

# LINK LIBRARI
target_link_libraries(unit_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)

