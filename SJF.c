#include <stdio.h>

void SJF() {
	const int job_size = 50;
	/* job contains accessible arrivalTime, serviceTime, and priority */
	struct job {
		int index;
		int arrive_T;
		int service_T;
		int priority;
	};

	struct job swap;
	struct job arrivalTime[job_size];
	/* job_array is list of jobs, currently blank */
	struct job job_array[job_size];

	/*maintaining consistent rand seed*/
	int seed = time(NULL);
	srand(seed);

	int w;
	for (w = 0; w < 5; w++) {
		int i;
		int k;
		int n;
		int currentTime = 0;
		int min;
		int m = 1;
		int servTime = 0;
		int quanta = 0;
		int quanta2 = 0;
		int counter = 0;
		int timeCount = 0;
		int totalWait = 0;
		int turn = 0;
		int turntotal = 0;
		int r = 0;
		int totalr = 0;

		printf("Shortest Job First on Run:%2d\n", w + 1);

		/*populating each job with data*/
		for (i = 0; i < job_size; i++) {
			job_array[i].index = i + 1;

			int arv = rand() % 100;
			job_array[i].arrive_T = arv;

			int ser = (rand() % 11);
			if (ser == 0)
				ser += 1;

			job_array[i].service_T = ser;

			int pr = rand() % 5;
			if (pr == 0)
				pr += 1;
			job_array[i].priority = pr;

		}

		//Initial sort based on arrival time
		for (i = 0; i < job_size - 1; i++) {
			for (k = 0; k < job_size - 1 - i; k++) {
				if (job_array[k].arrive_T > job_array[k + 1].arrive_T) {
					swap = job_array[k];
					job_array[k] = job_array[k + 1];
					job_array[k + 1] = swap;
				}
			}
		}

//Comparing arrival times and service times to sort based on which jobs are queued in the job pool.
		for (k = 0; k < job_size - 1; k++) {
			servTime = servTime + job_array[k].service_T;
			min = job_array[m].service_T;
			for (i = m; i < job_size - 1; i++) {
				if (servTime >= job_array[i].arrive_T
						&& job_array[i].service_T < min) {
					swap = job_array[m];
					job_array[m] = job_array[i];
					job_array[i] = swap;
				}
			}
			m++;
		}

//Loop used to calculate arrival time, service time, priority, average wait time, turnabout time, response time, and throughput
		for (m = 0; m <= job_size - 1 && currentTime < 100; m++) {

			//used to track quanta
			quanta = quanta2;
			quanta2 += job_array[m].service_T;
			//sets currentTime slice

			currentTime += job_array[m].service_T;

			//total wait time, used for calculation of average wait time. Wait time = Service time - Arrival time
			timeCount = currentTime - job_array[m].arrive_T;
			totalWait += timeCount;

			//total turnabout time, used for calculation of average turnabout time. Turnabout time = Wait time + Service Time
			turn = timeCount + job_array[m].service_T;
			turntotal += turn;

			//total response time, used for calculation of average response time.
			if (job_array[m].index == 1) {
				r = job_array[m].service_T;
			} else {
				r = job_array[m].service_T + job_array[m].arrive_T;
			}
			// r= currentTime + job_array[m].arrive_T
			totalr += r;

			//prints the array with a job, its arrival time, its service time, and priority
			printf(
					"quanta:%2d -%2d  | job:%2d | arrive time: %2d | service time: %2d | priority: %d \n",
					quanta, quanta2, job_array[m].index, job_array[m].arrive_T,
					job_array[m].service_T, job_array[m].priority);

			counter++;

		}
		//prints the averages
		printf("Average Wait Time:%f    ", (float) totalWait / counter);
		printf("Average TurnAbout Time:%f    ", (float) turntotal / counter);
		printf("Average Response Time:%f    ", (float) totalr / counter);
		printf("Throughput: %f   ", (float) counter / currentTime);
		printf("\n\n");
	}
	return;
}
