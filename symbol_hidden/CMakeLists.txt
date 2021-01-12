project(entry)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "")
set(CMAKE_C_FLAGS "")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden -fvisibility=hidden")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")

file(GLOB entry_SRC "entry.hpp" "entry.cpp")

add_library(${PROJECT_NAME} SHARED ${entry_SRC})