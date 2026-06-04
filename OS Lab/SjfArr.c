//SJF

#include<stdio.h>

struct Process

{

int pid;

int at, bt, ct, wt, tt;

};

typedef struct Process pr;

void main()

{

int n, i, j, t, b, pos;

float sumwt, sumtt;

sumwt=0;

sumtt=0;

printf("\nEnter the number of processes: ");

scanf("%d", &n);

pr p[n], temp;

printf("\nEnter the process id, arrival time and burst time of each process:\n");

for (i=0 ; i<n ; i++)

scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].bt);

for (i=0 ; i<n-1 ; i++)

{

for (j=i+1 ; j<n ; j++)

{

if (p[i].at > p[j].at)

{

temp = p[i];

p[i] = p[j];

p[j] = temp;}}}

for (i=0 ; i<n ; i++)

{

if (i != 0)

t = p[i-1].ct;

else

t = p[i].at;

b = p[i].bt;

for (j=i ; j<n ; j++)

{

if ((p[j].at <= t) && (p[j].bt <= b))

{

pos = j;

b = p[j].bt;

}

}

p[pos].ct = t + p[pos].bt;

p[pos].tt = p[pos].ct - p[pos].at;

p[pos].wt = p[pos].tt - p[pos].bt;

sumwt += p[pos].wt;

sumtt += p[pos].tt;

temp = p[pos];

p[pos] = p[i];

p[i] = temp;

}

for (i=0 ; i<n-1 ; i++)

{

for (j=i+1 ; j<n ; j++)

{

if (p[i].pid > p[j].pid)

{

temp = p[i];
p[i] = p[j];

p[j] = temp;

}

}

}

printf("\nProcess ID Arrival Time Burst Time Completion Time Waiting Time Turnaround Time\n");

for (i=0 ; i<n ; i++)

printf("%5d%15d%14d%15d%15d%15d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].wt, 

p[i].tt);

printf("\nAverage Waiting Time = %.3f", (sumwt/n));

printf("\nAverage Turnaroung Time = %.3f\n", (sumtt/n));}
