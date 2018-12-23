EXEC=test_mpi_bcast
MPI_ROOT=/opt/intel/compilers_and_libraries_2018.1.163/linux/mpi_2019/intel64

all: ${EXEC}
${EXEC}: test_mpi_bcast.o
	icc -o ${EXEC} test_mpi_bcast.o -g -L${MPI_ROOT}/lib/release -lmpi

test_mpi_bcast.o: test_mpi_bcast.cpp
	icc -c -g -std=c++11 test_mpi_bcast.cpp -o test_mpi_bcast.o -I${MPI_ROOT}/include
clean:
	rm -f ${EXEC} test_mpi_bcast.o
