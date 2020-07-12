SRC_COM = $(wildcard ./*.cc) $(wildcard ./algorithm_impls/*.cc)

SRC = $(SRC_COM)

# $@  表示目标文件
# $^  表示所有的依赖文件
# $<  表示第一个依赖文件
# $?  表示比目标还要新的依赖文件列表

CXX = g++
CXXFLAGS = -std=c++11 -g -O1
TARGET = test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf test test.dSYM

.PHONY: clean