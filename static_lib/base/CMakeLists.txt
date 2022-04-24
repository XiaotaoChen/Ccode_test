project(Base)
add_definitions(-O3 -Ofast -ffast-math)
add_definitions(-Wall -Wextra -Wno-unused-function)
add_definitions(-std=c++11 -fPIC)
# to avoid no return error(ToDo)
add_definitions(-Werror=return-type)

file(GLOB base_SRC "base.cpp")
add_library(base STATIC ${base_SRC})