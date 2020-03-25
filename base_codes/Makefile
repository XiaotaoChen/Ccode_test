
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

SRC_COM = $(wildcard algorithm_impls/*.cc) $(wildcard search_alg_impls/*.cc) $(wildcard dp_alg_impls/*.cc) $(wildcard sort_impls/*.cc) $(wildcard utils_impls/*.cc) \
          $(wildcard greedy_impls/*.cc) $(wildcard graph_alg_impls/*.cc) $(wildcard trackback_alg_impls/*.cc) $(wildcard dfs_alg_impls/*.cc) \
		  $(wildcard bfs_alg_impls/*.cc) $(wildcard stack_alg_impls/*.cc) $(wildcard heap_alg_impls/*.cc) $(wildcard binary_search_alg_impls/*.cc) \
		  $(wildcard merge_set_alg_impls/*.cc) $(wildcard listnode_alg_impls/*.cc) $(wildcard binary_pointer_alg_impls/*.cc) \
		  $(wildcard str_alg_impls/*.cc) $(wildcard topoloical_sort/*.cc) $(wildcard memory_alg_impls/*.cc) $(wildcard hash_alg_impls/*.cc) \
		  $(wildcard bits_alg_impls/*.cc) $(wildcard design_alg_impls/*.cc) $(wildcard dict_tree_alg_impls/*.cc) $(wildcard line_tree_alg_impls/*.cc) \
		  $(wildcard minimization_alg_impls/*.cc) $(wildcard random_sample_alg_impls/*.cc) $(wildcard geometric_alg_impls/*.cc)

SRC = test.cc $(SRC_COM)

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