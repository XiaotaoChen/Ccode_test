
# SRC = test.cc \
#     algorithm_impls/binary_tree.cc \
# 	algorithm_impls/string_alg.cc \
# 	algorithm_impls/reverse_polish.cc \
# 	algorithm_impls/max_point_on_a_line.cc \
# 	algorithm_impls/listnode.cc \
# 	algorithm_impls/word_break.cc \
# 	algorithm_impls/single_number.cc \
# 	algorithm_impls/candy.cc \
# 	algorithm_impls/complete_circuit.cc \
# 	algorithm_impls/undirectGraphNode.cc \
# 	algorithm_impls/palindrome.cc \
# 	algorithm_impls/surrounding_region.cc

SRC_COM = $(wildcard algorithm_impls/*.cc) $(wildcard search_alg_impls/*.cc)
SRC = test.cc $(SRC_COM)

CXX = g++
CXXFLAGS = -std=c++11 -g -O1
TARGET = test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf test test.dSYM

.PHONY: clean