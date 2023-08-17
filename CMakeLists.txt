cmake_minimum_required(VERSION 3.0.0)
project(polynomial VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

include_directories(inc/)
add_executable(polynomial src/main.c src/polynomial.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
