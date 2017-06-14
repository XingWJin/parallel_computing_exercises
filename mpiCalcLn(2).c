#include <stdio.h>
#include "mpi.h"


int main(int argc, char** argv)
{
	int i, N, noprocs, nid;
	float sum = 0, Gsum;
	MPI_Init(&argc, &argv);	/* initializes MPI */
	MPI_Comm_rank(MPI_COMM_WORLD, &nid);	/* get current process id */
	MPI_Comm_size(MPI_COMM_WORLD, &noprocs);	/* get number of processes */
	if (nid== 0){
		printf("The expected value for ln(2) is 0.69314718056 \n ");
		printf("Please enter the number of items to sum \n"); 
		scanf("%d", &N);
	}
	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);	/*memory address;num of data items;data types;rank of processor
													doing broadcasting;communicator*/
	for (i = nid; i < N; i += noprocs){
		if (i % 2)
			sum -= (float)1 / (i + 1);
		else
			sum += (float)1 / (i + 1);
	}
	MPI_Reduce(&sum, &Gsum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD); /*memory address storing the data being sent;
																	   address storing received data;num of data items sent;
																	   data types;reduction operation (here,sum);rank of processor to receive data;
																	   communicator across which reduction is done*/
	if (nid == 0)
		printf("An estimate of ln2 is %f \n", Gsum);
	MPI_Finalize();

}
