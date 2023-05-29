cmake_minimum_required(VERSION 3.5)
project(iFollow)

include_directories(
  includes/
)

add_executable(solution
  src/main.cpp
  src/AlarmManager.cpp
)

add_executable(runTests
  src/alarmTest.cpp
  src/AlarmManager.cpp
)

target_link_libraries(runTests gtest gtest_main)

