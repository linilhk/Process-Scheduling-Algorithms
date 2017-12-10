#include <stdio.h>
#include"FCFS.c"
#include"HPF_np.c"
#include"HPF_p.c"
#include"RR.c"
#include"SJF.c"
#include"SRT.c"

void main()
{
    FCFS();
    SJF();
    SRT();
    RR();
    HPF_np();
    HPF_p();
}
