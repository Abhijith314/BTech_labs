#include<stdio.h>
struct data {
int p_no,bt_tm,arr,tat,wt,taat;
};
void main()
{
int i,j,n;
float atat,awt,tta=0,tat=0,taat=0,twt,ttat=0;
printf("Enter the number of process : ");
scanf("%d",&n);
struct data p[n],temp;
int c[n];

printf("Enter the Process no. Arrival time and Burst time of :\n");
for(i=0;i<n;i++)
{
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
for(i=0;i<n;i++) {
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
for(i=0;i<n;i++)
{
printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].p_no,p[i].arr,p[i].bt_tm,p[i].tat,p[i].wt);
}
printf("the average turnaround time:%f\n",atat);
printf("the average waiting time:%f\n",awt);
}
