cmake_minimum_required(VERSION 3.16)

# Set project name
project(DistinctKmerTest)

# Gather all test cpp files
file(GLOB_RECURSE SOURCES "*.cpp")

# Build test executables from sources
add_executable(${PROJECT_NAME} ${SOURCES})

# Add Options
enable_code_coverage(${PROJECT_NAME})

# Link libraries
target_link_libraries(${PROJECT_NAME} DistinctKmerLib)
target_link_libraries(${PROJECT_NAME} gtest_main)

# Include header files
target_include_directories(${PROJECT_NAME} PRIVATE $<TARGET_PROPERTY:DistinctKmerLib,INCLUDE_DIRECTORIES>)
target_include_directories(${PROJECT_NAME} PRIVATE $<TARGET_PROPERTY:gtest_main,INCLUDE_DIRECTORIES>)

# Build with C++20
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

# Add test to run
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

# Output destination for library
install(TARGETS ${PROJECT_NAME} DESTINATION "test")