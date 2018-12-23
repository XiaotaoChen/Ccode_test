#include "mpi.h"
#include <iostream>

int main(int argc, char **argv)
{
	int myid, numprocs;
	MPI_Init(NULL, NULL);
        //MPI_Comm_dup(MPI_COMM_WORLD, &(horovod_global.mpi_comm));
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	int loops=10;
        int RANK_ZERO=0;
	for(int i=0;i<loops;i++){
	if(0 == myid) {
           int encoded_length=i;
           MPI_Bcast(&encoded_length, 1, MPI_INT, RANK_ZERO, MPI_COMM_WORLD);
 	   int encoded_length2=i+100;
           MPI_Bcast(&encoded_length2, 1, MPI_INT, RANK_ZERO, MPI_COMM_WORLD);
           std::cout<<"rank: "<<myid<<" bcast number: "<<encoded_length<<std::endl;
	} else {
	   int recev_length;
           MPI_Bcast(&recev_length, 1, MPI_INT, RANK_ZERO, MPI_COMM_WORLD);
           std::cout<<"rank: "<<myid<<", i="<<i<<", recev_length == bcast number "
                     <<recev_length<<std::endl;

          // if(i==recev_length)
          // 	std::cout<<"rank: "<<myid<<", i="<<i<<", recev_length == bcast number "
          //               <<recev_length<<std::endl;
	  // else{
	  //      std::cout<<"rank: "<<myid<<", i="<<i<<", recev_length != bcast number"
          //               <<recev_length<<std::endl;
    	  //      break;
	  // }
        }
	}
	MPI_Finalize();
}
