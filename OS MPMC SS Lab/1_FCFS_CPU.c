#include<stdio.h>
struct data {
int p_no,bt_tm,arr,tat,wt;
};
void main()
{
int i,j,n;
float atat,awt,twt,ttat=0;
printf("Enter the number of process : ");
scanf("%d",&n);
struct data p[n],temp;
int c[n];

printf("Enter the Process no. Arrival time and Burst time of :\n");
for(i=0;i<n;i++) {
printf("Process %d : ",i);
scanf("%d %d %d",&p[i].p_no,&p[i].arr,&p[i].bt_tm);
c[i]=0;
}
for(i=0;i<n;i++) {
    for(j=i+1;j<n;j++) {
        if(p[i].arr>p[j].arr) {
            temp=p[i];
            p[i]=p[j];
            p[j]=temp;
        }
    }
}
i=0;
c[i]=c[i]+p[i].bt_tm;
p[i].tat=c[i]-p[i].arr;
ttat=ttat+p[i].tat;
for(i=1;i<n;i++) {
    c[i]=c[i-1]+p[i].bt_tm;
    p[i].tat=c[i]-p[i].arr;
    ttat=ttat+p[i].tat;
}
for(i=0;i<n;i++) {
    p[i].wt=p[i].tat-p[i].bt_tm;
    twt=twt+p[i].wt;
}
atat=ttat/n;
awt=twt/n;
printf("GANTT CHART\n0");
for(i=0;i<n;i++) {
    printf("\tP%d\t%d",p[i].p_no,c[i]);
}
printf("\nProcess no.\tArrival time\tBurst time\tTurnaround time\tWaiting time\n");
for(i=0;i<n;i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].p_no,p[i].arr,p[i].bt_tm,p[i].tat,p[i].wt);
}
printf("the average turnaround time:%f\n",atat);
printf("the average waiting time:%f\n",awt);
}

/*
OUTPUT

Enter the number of process : 5
Enter the Process no. Arrival time and Burst time of :
Process 0 : 1 2 2
Process 1 : 2 5 6
Process 2 : 3 0 4
Process 3 : 4 4 7
Process 4 : 5 7 4
GANTT CHART
0       P3      4       P1      6       P4      13      P2      19      P5      23
Process no.     Arrival time    Burst time      Turnaround time Waiting time
3               0               4               4               0
1               2               2               4               2
4               4               7               9               2
2               5               6               14              8
5               7               4               16              12
the average turnaround time:9.400000
the average waiting time:4.800000
*/