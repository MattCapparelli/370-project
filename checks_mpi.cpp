//checks_mpi.cpp

#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>

#define CHECK_COUNT 8
#define BANK_COUNT 2
#define CUSTOMER_COUNT 2

int main (int argc,  char *argv[])
{
	//Declare all variables
	int myid, numprocs;
	int startIndex, endIndex;
	int namelen, checksPart, checksPart0;
	int checks[CHECK_COUNT][3];
	double startTime, endTime, totalTime;
	MPI_Status status;

	char processor_name[MPI_MAX_PROCESSOR_NAME];

	//Set up MPI environment
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Get_processor_name(processor_name, &namelen);
 
	fprintf(stderr, "process %d on %s\n", myid, processor_name);
	fflush(stderr);  
	
	//Generate data for the checks (accessible by all procs)
	for (int i=0; i<CHECK_COUNT; i++) {

		//Generate bank id number (index=0)
		checks[i][0] = (rand() % BANK_COUNT) + 1;
			
		//Generate account id number (index=1)
		checks[i][1] = (rand() % CUSTOMER_COUNT) + 1;
		
		//Generate check id number (index=2)
		checks[i][2] = (rand() % 999) + 1;	
	}
	
	//Master process
	if (myid == 0) {
		
		//Print initial check data
		printf("Check count = %d\n",CHECK_COUNT);
		printf("Bank count = %d\n",BANK_COUNT);
		printf("Customer count = %d\n",CUSTOMER_COUNT);
		printf("\n");
		if (CHECK_COUNT <= 20) {
			printf("Initial check data:\n");
			for (int i=0; i<CHECK_COUNT; i++) {
				printf("%010d  %010d  #%03d\n",checks[i][0],checks[i][1],checks[i][2]);
			}
		}
		
		//Start the timer
		startTime = MPI_Wtime();
	
		//Process 0 divides work among processes
		checksPart = (int)floor(CHECK_COUNT/numprocs);
		checksPart0 = checksPart + CHECK_COUNT%numprocs;
	}

	MPI_Bcast(&checksPart, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&checksPart0, 1, MPI_INT, 0, MPI_COMM_WORLD);

	startIndex = checksPart0 + (myid-1)*checksPart;
	endIndex = startIndex + checksPart; 
	
	//Each process sorts their portion of the checks
	if (myid == 0) //master's work
	{  
		bool swapped = true;
		while (swapped) {
			swapped = false;
			
			/*
			//DELETE ME LATER
			bool yes = false;
			*/
			
			for (int j=1; j<checksPart0; j++) {
				
				/*
				//DELETE ME LATER
				yes = false;
				*/
				
				if (checks[j][0] < checks[j-1][0]) {
					
					int temp[3];
					temp[0] = checks[j][0];
					temp[1] = checks[j][1];
					temp[2] = checks[j][2];
					
					checks[j][0] = checks[j-1][0];
					checks[j][1] = checks[j-1][1];
					checks[j][2] = checks[j-1][2];
					
					checks[j-1][0] = temp[0];
					checks[j-1][1] = temp[1];
					checks[j-1][2] = temp[2];
					
					swapped = true;
					
					/*
					yes = true;
					//DELETE ME LATER
					printf("BANK IDS -");
					*/
					
				} 
				//Compare account id's if bank id's are the same
				else if (checks[j][0] == checks[j-1][0] && checks[j][1] < checks[j-1][1]) {
						
					int temp[3];
					temp[0] = checks[j][0];
					temp[1] = checks[j][1];
					temp[2] = checks[j][2];
					
					checks[j][0] = checks[j-1][0];
					checks[j][1] = checks[j-1][1];
					checks[j][2] = checks[j-1][2];
					
					checks[j-1][0] = temp[0];
					checks[j-1][1] = temp[1];
					checks[j-1][2] = temp[2];
					
					swapped = true;
					
					/*
					yes = true;
					//DELETE ME LATER
					printf("ACCOUNT IDS - ");
					*/
				} 
				//Compare check id if account id and bank id are the same
				else if (checks[j][0] == checks[j-1][0]) {
					if (checks[j][1] == checks[j-1][1] && checks[j][2] < checks[j-1][2]) {
							
						int temp[3];
						temp[0] = checks[j][0];
						temp[1] = checks[j][1];
						temp[2] = checks[j][2];
						
						checks[j][0] = checks[j-1][0];
						checks[j][1] = checks[j-1][1];
						checks[j][2] = checks[j-1][2];
						
						checks[j-1][0] = temp[0];
						checks[j-1][1] = temp[1];
						checks[j-1][2] = temp[2];
					
						swapped = true;
						
						/*
						yes = true;
						//DELETE ME LATER
						printf("CHECK NUMBER - ");
						*/
					}
				}
				/*
				//DELETE ME LATER
				if (yes){
					printf("SWAPPING index %d and %d\n",j,j-1);
					for (int i=0; i<CHECK_COUNT; i++) {
						printf("%d %d #%d\n",checks[i][0],checks[i][1],checks[i][2]);
					}
				}
				else {
					printf("No swap for inex %d and %d\n",j,j-1);
				}
				*/
				
			}
		}
	}
	else //slave's work
	{
		bool swapped = true;
		while (swapped) {
			swapped = false;
			
			
			//DELETE ME LATER
			bool yes = false;
			
			
			for (int j=startIndex+1; j<endIndex; j++) {
				
				
				//DELETE ME LATER
				yes = false;
				
				
				if (checks[j][0] < checks[j-1][0]) {
					
					int temp[3];
					temp[0] = checks[j][0];
					temp[1] = checks[j][1];
					temp[2] = checks[j][2];
					
					checks[j][0] = checks[j-1][0];
					checks[j][1] = checks[j-1][1];
					checks[j][2] = checks[j-1][2];
					
					checks[j-1][0] = temp[0];
					checks[j-1][1] = temp[1];
					checks[j-1][2] = temp[2];
					
					swapped = true;
					
					
					yes = true;
					//DELETE ME LATER
					printf("BANK IDS -");
					
					
				} 
				//Compare account id's if bank id's are the same
				else if (checks[j][0] == checks[j-1][0] && checks[j][1] < checks[j-1][1]) {
						
					int temp[3];
					temp[0] = checks[j][0];
					temp[1] = checks[j][1];
					temp[2] = checks[j][2];
					
					checks[j][0] = checks[j-1][0];
					checks[j][1] = checks[j-1][1];
					checks[j][2] = checks[j-1][2];
					
					checks[j-1][0] = temp[0];
					checks[j-1][1] = temp[1];
					checks[j-1][2] = temp[2];
					
					swapped = true;
					
					
					yes = true;
					//DELETE ME LATER
					printf("ACCOUNT IDS - ");
					
				} 
				//Compare check id if account id and bank id are the same
				else if (checks[j][0] == checks[j-1][0]) {
					if (checks[j][1] == checks[j-1][1] && checks[j][2] < checks[j-1][2]) {
							
						int temp[3];
						temp[0] = checks[j][0];
						temp[1] = checks[j][1];
						temp[2] = checks[j][2];
						
						checks[j][0] = checks[j-1][0];
						checks[j][1] = checks[j-1][1];
						checks[j][2] = checks[j-1][2];
						
						checks[j-1][0] = temp[0];
						checks[j-1][1] = temp[1];
						checks[j-1][2] = temp[2];
					
						swapped = true;
						
						
						yes = true;
						//DELETE ME LATER
						printf("CHECK NUMBER - ");
						
					}
				}
				
				//DELETE ME LATER
				if (yes){
					printf("SWAPPING index %d and %d\n",j,j-1);
					for (int i=0; i<CHECK_COUNT; i++) {
						printf("%d %d #%d\n",checks[i][0],checks[i][1],checks[i][2]);
					}
				}
				else {
					printf("No swap for inex %d and %d\n",j,j-1);
				}
				
				
			}
		}
	}

	//Merge sorted lists together
	MPI_Gather(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator)
	

	
	if (myid == 0) 
	{
		
		
		
		printf("MERGING SORTED LISTS NOT IMPLEMENTED YET\n");
		
		
		
		endTime = MPI_Wtime();
		totalTime = endTime - startTime;
		
		if (CHECK_COUNT <= 20) {
			printf("Sorted check data:\n");
			for (int i=0; i<CHECK_COUNT; i++) {
				printf("%010d  %010d  #%03d\n",checks[i][0],checks[i][1],checks[i][2]);
			}
		}
		printf("Timing: %f\n",totalTime);
	}

	MPI_Finalize();

 }