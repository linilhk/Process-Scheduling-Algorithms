#include <stdio.h>

void RR() {

	int a;					// job variable
	int seed;
	int holder;
	seed = time(NULL);
	srand(seed);					// guarantee consistency when debugging

	for (a = 0; a < 5; a++) {
		int index;
		int n = 7; //variable for number of processes input
		int timeQ; //current and also the total index of time slice
		int remain; //variable remain process to do
		int flag = 0; //same as flag set to false but for int variable
		int time_slice = 1; // >>>>>SET TIME SLICE HERE<<<<
		int wait_time = 0; //time period between service time and the arrival time (st - at)
		int turnaround_time = 0; //total time it take to finished the process's service time
		int arrival_time[100]; //
		int service_time[100]; //aka burst time and the amount of quantum's unit need to finished process
		int remaining_time[100]; //remaining process's service time till completion
		int response_time[100]; // [(first arrival time) - (service time)]
		//Get the number of processes input
		printf("\nRound robin (RR) Run #%d\n", a+1);
		printf("Automatic Set: Number of Process = %d\n", n);

		remain = n; //remaining processes = number of inputted process

		printf("Automatic Set: Time Slice/Quantum = %d\n", time_slice);
		//Getting the Arrival Time and Service Time inputs for each processes
		for (index = 0; index < n; index++) {

			arrival_time[index] = rand() % 10; // will return num between 0 and 10
			service_time[index] = (rand() % 100); //will return num between 0 and 99

			printf(
					"P[%d]: Random Service Time = %d      |      Random Arrival Time =: %d\n",
					index + 1, service_time[index], arrival_time[index]);

			if (service_time[index] == 0) {
				service_time[index] += 1; // service_time = 0.1 .. 10
			}

			//set remaining time equal the value of service time for the given process
			remaining_time[index] = service_time[index];

		}

		printf("\nProcess\t|Turnaround Time|Waiting Time|Response Time\n");
		for (timeQ = 0, index = 0; remain != 0;) {
			//If remaining service time is <= time slice and > 0, process is finished.
			//And reset the remaining_time to 0 to hold value for the next process
			if (remaining_time[index] <= time_slice
					&& remaining_time[index] > 0) {

				timeQ += remaining_time[index];
				remaining_time[index] = 0;
				flag = 1; //flag set to true as an indicator for the current process is finished
			}
			//else if remaining time > 0 only, remainig time = (remaining time - time slice)
			//time = time + time slice
			else if (remaining_time[index] > 0) {
				remaining_time[index] -= time_slice;
				timeQ += time_slice; //increase time slice by it current length amount
			}

			//if remaining time reset back to zero and the last process is finished, minus lenght
			if (remaining_time[index] == 0 && flag == 1) {
				remain--; //minus lenght of the process's queue by 1

				response_time[index] = timeQ - service_time[index]
						- arrival_time[index];
				holder += timeQ - service_time[index]; //holder total response time of loops
				//print current finished process's turnaround and waiting times
				printf("P[%d]\t|\t%d\t|\t%d|\t%d\t|\n", index + 1,
						timeQ - arrival_time[index],
						timeQ - arrival_time[index] - service_time[index],
						response_time[index]);

				wait_time += timeQ - arrival_time[index] - service_time[index]; //calc current avg wait time

				turnaround_time += timeQ - arrival_time[index]; //calc current avg turnaround time
				flag = 0; //this mean the current process have not finished
			}

			//determining the next index of a process to go next by the current arriving time
			if (index == n - 1) {
				index = 0;
			} else if (arrival_time[index + 1] <= timeQ) {
				{
					index++;
				}
			} else {
				index = 0;
			}
		}
		printf("\nAverage Waiting Time= %f\n", wait_time * 1.0 / n);
		printf("Average Turnaround Time = %f\n", turnaround_time * 1.0 / n);
		printf("Average Response Time = %f\n", holder * 1.0 / n);
		printf(
				"_________________________________________________________________________________");
		holder = 0;

	}
}
