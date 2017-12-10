#include <stdio.h>

void FCFS()
{
    const int job_Size = 70;

    /*maintaining consistent rand seed*/
    int seed = time(NULL);
	srand(seed);

    /* job contains accessible arrivalTime, serviceTime, and priority */
    struct job
    {
        int index;      //for job name
        int arrive_T;
        int service_T;
        int priority;
    };

    /* job_array is list of jobs, currently blank */
 	struct job job_array[job_Size];

    //Run 5 times
    int a;
    for (a = 0; a <5; a++)
    {
        int waiting_T;
        int total_Wait = 0;
        int turnaround_T;
        int total_Ta = 0;
        int response_T;
        int total_R = 0;
        int finished_Job = 0;

        printf("First-come first-served (FCFS) Run #%d\n", a+1);


        /*populating each job with data*/
        int i;
        for (i = 0 ; i < job_Size ; i++)
        {
            job_array[i].index = i+1;

            job_array[i].arrive_T = rand() % 100;

            int ser = (rand() % 11);
            if (ser == 0)
                ser += 1;
            job_array[i].service_T = ser;

            int pr = rand() % 5;
            if (pr == 0)
                pr += 1;
            job_array[i].priority = pr;
        }

        /*
        printf("\n\nBefore sorted:\n\n");
        for (i = 0; i < job_Size; i++)
        {
            printf("job %d:\n", i+1);
            printf("job name: P%d\n", job_array[i].index);
            printf("arrive time: %d\n", job_array[i].arrive_T);
            printf("service time: %d\n", job_array[i].service_T);
            printf("priority: %d\n\n", job_array[i].priority);
        }
        */

        //sorting jobs by arrive time
        int k;
        struct job swap;
        for(i = 0; i < job_Size-1; i++)
        {
            for(k = 0; k < job_Size - 1 - i; k++)
            {
                if (job_array[k].arrive_T > job_array[k+1].arrive_T)
                {
                    swap = job_array[k];
                    job_array[k] = job_array[k+1];
                    job_array[k+1] = swap;
                }
            }
        }

        /*
        printf("\n\nAfter sorted by arrive time:\n\n");
        for (i = 0; i < job_Size; i++)
        {
            printf("job %d:\n", i+1);
            printf("job name: P%d\n", job_array[i].index);
            printf("arrive time: %d\n", job_array[i].arrive_T);
            printf("service time: %d\n", job_array[i].service_T);
            printf("priority: %d\n\n", job_array[i].priority);
        }
        */

        int time_slice = 0;
        for (i = 0; i < job_Size && time_slice < 100; i++)
        {
            if (job_array[i].arrive_T > time_slice)
            {
                printf("quanta %2d -", time_slice);
                time_slice = job_array[i].arrive_T;
                printf("%3d :  idle\n", time_slice);
            }
            waiting_T = time_slice - job_array[i].arrive_T;
            response_T = waiting_T;
            total_Wait += waiting_T;
            total_R += response_T;
            turnaround_T = waiting_T + job_array[i].service_T;
            total_Ta += turnaround_T;
            printf("quanta %2d -", time_slice);
            time_slice += job_array[i].service_T;
            printf("%3d :  ", time_slice);
            printf("job %2d: P%2d, ", i+1, job_array[i].index);
            printf("arrive time: %2d, service time: %2d, priority: %d, ", job_array[i].arrive_T, job_array[i].service_T, job_array[i].priority);
            printf("waiting time: %2d, turnaround time: %2d , response time: %2d\n", waiting_T, turnaround_T, response_T);
            finished_Job++;
        }

        printf("Average waiting time: %.5f   ", (float)total_Wait/finished_Job);
        printf("Average turnaround time: %.5f   ", (float)total_Ta/finished_Job);
        printf("Average response time: %.5f   ", (float)total_R/finished_Job);
        printf("Throughput: %.5f\n\n", (float)finished_Job/time_slice);
    }
    return;
}

