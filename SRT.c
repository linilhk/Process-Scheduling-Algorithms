#include <stdio.h>

void SRT() {
	/*maintaining consistent rand seed*/
	int seed = time(NULL);
	srand(seed);

	//Create 5 iterations
	int w;
	for (w = 0; w < 5; w++) {
		// array of arrival time, burst time, remaining time, and list of process
		int arrivalTime[100], burstTime[100], remainingTime[100];
		int endTime, i, smallest, time2;
		int remain = 0;
		int maxJobs = 25;
		int Waiting = 0;
		int turnAround = 0;
		int quanta = 0, quanta2 = 0;
		int currentTime = 0, timer = 0;
		int counter = 0, counter2 = 0;

		printf("Shortest Remaining Time Run:%2d\n", w + 1);

		// set the initial arrival and burst time
		for (i = 0; i < maxJobs; i++) {
			int arv = rand() % 100;
			arrivalTime[i] = arv;

			int ser = (rand() % 11);
			if (ser == 0)
				ser += 1;

			burstTime[i] = ser;
			remainingTime[i] = burstTime[i];
		}
		remainingTime[99] = 9999;	// max

		//Creates and lists the quanta ranges for each job
		printf("List of quanta:");
		int m;
		for (m = 0; m < maxJobs - 1 && currentTime < 100; m++) {
			quanta = quanta2;
			quanta2 += burstTime[m];
			currentTime += burstTime[m];
			counter++;
			counter2 = counter;
			printf("\n%2d -%2d", quanta, quanta2);
		}
		printf("\nProcess\t|Turnaround Time| Waiting Time");
		printf("\n Corresponding Jobs:");

		//  Sort runningProcessList by Shortest Remaining Time
		for (time2 = 0; remain != maxJobs && timer != counter; time2++) {
			smallest = 99;
			// Start a loop where time starts from 0
			for (i = 0; i < maxJobs; i++) {
				//Find a process which have the least remaining time
				if (arrivalTime[i] <= time2
						&& remainingTime[i] < remainingTime[smallest]
						&& remainingTime[i] > 0) {
					smallest = i;
				}
			}
			//remainingtime is decremented by 1, since time is increased by 1
			remainingTime[smallest]--;

			// The process to run is the process on top of runningProcessList
			if (remainingTime[smallest] == 0)// if remainingtime of one process = 0
					{
				timer++;
				remain++;
				endTime = time2 + 1;// Variable time stores the current time, and the process was running at this moment, therefore its ending time = time+1
				printf("\nP%d\t|\t%d\t|\t%d", smallest + 1,
						endTime - arrivalTime[smallest],
						endTime - burstTime[smallest] - arrivalTime[smallest]); // print out process, turnarounf time and waiting time
				Waiting += endTime - burstTime[smallest]
						- arrivalTime[smallest];//Since burst time + waiting time = end time - Start time.therefore waiting time = end Time - burst time - arrival time
				turnAround += endTime - arrivalTime[smallest];// Turn arround = End time - arrival time
			}
		}

		// Print the average waiting and turnaround time where maxJobs is the number of process
		printf("\nAverage waiting time = %f\n", Waiting * 1.0 / maxJobs);
		printf("Average Turnaround time = %f\n\n", turnAround * 1.0 / 5);

	}
}
