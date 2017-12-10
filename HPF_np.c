#include <stdio.h>

void HPF_np()
{

		/*define job and job arrays*/
		typedef struct job
	{
		int started;
		char index;
		int arrive_T;
		int service_T;
		int priority;
		int remain_T;
		int waiting_T;
		int tempstop_T;
		int start_T;
	}job;

		const int job_size = 25;



	/*maintaining consistent rand seed*/

	int seed = time(NULL);
	//printf("%d   \n",seed);
	srand(seed);

int run;
for(run = 0 ; run < 5 ; run ++)
{
	job job_array[job_size];
	/*shuffle a array of INTs from 0-99
	 * guarentee to have no duplicates*/
	int tempArrive[100];
        int i;
		for (i = 0; i < 100; i++)
		{     // fill array
			tempArrive[i] = i;
		}
		for (i = 0; i < 100; i++)
		{    // shuffle array
			int temp = tempArrive[i];
			int randomIndex = rand() % 100;

			tempArrive[i] = tempArrive[randomIndex];
			tempArrive[randomIndex] = temp;
		}

		/*populating each job with data*/
	for (i = 0 ; i < job_size ; i++)
	{
		job_array[i].arrive_T = tempArrive[i]; //setting Arrive Time from INT array

		int ser = (rand() % 11); // service time
		if (ser == 0) ser += 1;

		job_array[i].service_T = ser;

		int pr = rand() % 5; //priority
		if (pr == 0) pr += 1;
		job_array[i].priority = pr;



	}
	/*sorting the job array using insertion*/
	int j;
	for (i = 0 ; i < job_size ; i++)
	{
		job tmp = job_array[i];

		for (j = i; j >= 1 && tmp.arrive_T < job_array[j-1].arrive_T; j--)
				job_array[j] = job_array[j-1];

		job_array[j] = tmp;
	}

	/*setting a name using CHAR for each job for job.index*/
	char arr[27];
	for(i = 0 ; i < job_size ; i++)
	{

		job_array[i].index = 'a'+i;

	//printf("%c,  ArriveTime: %2i , ServiceTime: %2i , Priority: %i , \n", job_array[i].index, job_array[i].arrive_T, job_array[i].service_T, job_array[i].priority);
	}




	/* 1.initialize variable for current job being worked on
	 * 2.initialize int checking if there is a job being worked on. */
	job current = {0};
	int currExist = 0;

	/*****************RECORDS || QUEUE   IMPLEMENTATION*************/
	/*RECORDS DEFINITION */
	typedef struct record
	{
		int completed;
		int turn_T;
		int wait_T;
		int response_T;
	}record;

	/*each priority queue has its own stats*/
	 record totalR = {0};
	 record lvl1R = {0};
	 record lvl2R = {0};
	 record lvl3R = {0};
	 record lvl4R = {0};



	/*helper function to record data*/

	void recordNest(job j, record* tot, record* lvl)
	{
			int wait= j.waiting_T;
			int turn= j.waiting_T + j.service_T;
			int response = j.start_T - j.arrive_T;
			tot->completed += 1;
			tot->turn_T += turn;
			tot->wait_T += wait;
			tot->response_T += response;

			lvl->completed += 1;
			lvl->turn_T += turn;
			lvl->wait_T += wait;
			lvl->response_T += response;
	}
	/*records data from job AFTER job COMPLETION*/
	void recordR(job j)
	{
		//printf("recording data \n");
			switch(j.priority)
			{
				case 1:
				recordNest(j, &totalR, &lvl1R);
				break;
				case 2:
				recordNest(j, &totalR, &lvl2R);
				break;
				case 3:
				recordNest( j, &totalR, &lvl3R);
				break;
				case 4:
				recordNest(j, &totalR, &lvl4R);

			}
	}
	/*END RECORDS DEFINITION*/

	/*QUEUE DEFINITION*/
	/* A job QUEUE with add/remove/checkempty/peek
	 * NOTE= front/back starts not at -1 since need INSERT FRONT ability*/
	typedef struct queue
	{
		job array[50];
		int front;
		int rear;
		int count;
	}queue;

	void enqueue (queue* q, job j)
	{
		if (q->rear == 50 - 1)
			printf("Queue Overflow \n");
		else
		{
			if(q->front == 0) q->front =1;
			q->rear +=1;
			q->count +=1;
			q->array[q->rear] = j;
		}
	}
	int hasQueue(queue q)
	{
		if( q.count > 0)
			return 1;
		else
			return 0;
	}
	job dequeue(queue* q)
	{
		if (q->front == -1 || q->front > q->rear)
		{
			printf("Queue Underflow \n");
			return ;
		}
		else
		{
			q->count -= 1;
			q->front +=1;
			return q->array[q->front-1];
		}
	}

	job peek(queue q)
	{
		return q.array[q.front];
	}

	/*END QUEUE DEFINITION*/

	queue lvl1 = {0};
	queue lvl2 = {0};
	queue lvl3 = {0};
	queue lvl4 = {0};



	/************ SCHEDULER IMPLEMENTATION************/

    printf("\nHighest priority first (HPF) (non-preemptive) Run #%d\n", run+1);
	/* set job as CURRENT, begin work on a job*/
	void work(job j, int time)
	{
		currExist = 1;
		current = j;
			printf("starting [ %c ] P: %d, T: %d \n", current.index, current.priority, time);
			current.waiting_T =0;
			current.waiting_T += time - current.arrive_T;
			current.remain_T = current.service_T;
			current.start_T = time;
	}


	int nextIndexJob = 0;

	/* moving from timeslice to timeslice*/
	for(i = 0; i<100; i++)
	{
		if(job_array[nextIndexJob].arrive_T == i) // enter if new job found arriving
		{
			job temp = job_array[nextIndexJob];
			nextIndexJob +=1;

			/*add new job to its priority queue*/
			switch(temp.priority)
			{
				case 1:
				enqueue(&lvl1, temp);
				break;
				case 2:
				enqueue(&lvl2, temp);
				break;
				case 3:
				enqueue(&lvl3, temp);
				break;
				case 4:
				enqueue(&lvl4, temp);
			}
		}

		/*If there are no jobs currently working, pick highest priority queue to choose job from*/
		if(currExist == 0)
		{
			if(hasQueue(lvl1) == 1)
			work(dequeue(&lvl1), i); 		// i is timeslice
			else if(hasQueue(lvl2) == 1)
			work(dequeue(&lvl2), i);
			else if(hasQueue(lvl3) == 1)
			work(dequeue(&lvl3), i);
			else if(hasQueue(lvl4) == 1)
			work(dequeue(&lvl4), i);
		}

		/*Work on the current Job, if complete, set current job to not exist*/
		if(currExist == 1)
		{
			current.remain_T = current.remain_T -1;
				if(current.remain_T == 0)
				{
					currExist = 0;
					recordR(current);
					}

		}
	}
	/*end time loop*/

/*Calculate average Turnaround Time/Waiting Time/Response Time*/
	double totalTurn = (double)totalR.turn_T/totalR.completed;
	double totalWait = (double)totalR.wait_T/totalR.completed;
	double totalRes = (double)totalR.response_T/totalR.completed;
	double throughput = (double)totalR.completed/100;

	double lvl1Turn= (double)lvl1R.turn_T/lvl1R.completed;
	double lvl1Wait= (double)lvl1R.wait_T/lvl1R.completed;
	double lvl1Res= (double)lvl1R.response_T/lvl1R.completed;
	double throughput1 = (double)lvl1R.completed/100;

	double lvl2Turn= (double)lvl2R.turn_T/lvl2R.completed;
	double lvl2Wait= (double)lvl2R.wait_T/lvl2R.completed;
	double lvl2Res= (double)lvl2R.response_T/lvl2R.completed;
	double throughput2 = (double)lvl2R.completed/100;

	double lvl3Turn= (double)lvl3R.turn_T/lvl3R.completed;
	double lvl3Wait= (double)lvl3R.wait_T/lvl3R.completed;
	double lvl3Res= (double)lvl3R.response_T/lvl3R.completed;
	double throughput3 = (double)lvl3R.completed/100;

	double lvl4Turn= (double)lvl4R.turn_T/lvl4R.completed;
	double lvl4Wait= (double)lvl4R.wait_T/lvl4R.completed;
	double lvl4Res= (double)lvl4R.response_T/lvl4R.completed;
	double throughput4 = (double)lvl4R.completed/100;

	printf("Total Average Turnaround: %.2f, Average Wait: %.2f, Average Response Time: %.2f, Throughput: %.2f  \n", totalTurn, totalWait, totalRes,  throughput);
	printf("Priority 1 Average Turnaround: %.2f, Average Wait: %.2f, Average Response Time: %.2f, Throughput: %.2f  \n", lvl1Turn, lvl1Wait, lvl1Res,  throughput1);
	printf("Priority 2 Average Turnaround: %.2f, Average Wait: %.2f, Average Response Time: %.2f, Throughput: %.2f  \n", lvl2Turn, lvl2Wait, lvl2Res,  throughput2);
	printf("Priority 3 Average Turnaround: %.2f, Average Wait: %.2f, Average Response Time: %.2f, Throughput: %.2f  \n", lvl3Turn, lvl3Wait, lvl3Res,  throughput3);
	printf("Priority 4 Average Turnaround: %.2f, Average Wait: %.2f, Average Response Time: %.2f, Throughput: %.2f  \n", lvl4Turn, lvl4Wait, lvl4Res, throughput4);
}
}
