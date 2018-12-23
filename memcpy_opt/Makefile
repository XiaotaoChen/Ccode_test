ifeq ($(CXX), icpc)
	#CXXFLAGS=-O3 -xCOMMON-AVX512 -qopenmp -std=c++11 -qopt-prefetch=3
	CXXFLAGS=-O3 -qopenmp -std=c++11 -qopt-prefetch=3 -march=native
	OBJ=memory_test.icpc
else
	CXXFLAGS=-O3 -fopenmp -std=c++11 -march=native
	OBJ=memory_test.g++
endif

SRC=memory_test.cc

.PHONY: all

all: $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $(OBJ)

clean:
	@rm -vf memory_test.g++ memory_test.icpc
