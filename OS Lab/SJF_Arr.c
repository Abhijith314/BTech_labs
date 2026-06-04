#include<stdio.h>
struct process {
int pno,at,bt,ct,tt,wt;
};
void main()
{
int n,i,j,pos,t,b;
float sumtt=0,sumwt=0,atwt,atat;
printf("Enter the number of process : ");
scanf("%d",&n);
struct process p[n],temp;
printf("Enter the Process no. Arrival time and Burst time of :-\n");
for(i=0;i<n;i++) {
printf("Process : ");
scanf("%d %d %d",&p[i].pno,&p[i].at,&p[i].bt);
}
for(i=0;i<n-1;i++){
for(j=i+1;j<n;j++){
if(p[i].at>p[j].at){
temp=p[i];
p[i]=p[j];
p[j]=temp;
}
}
}
for(i=0;i<n;i++) {
if(i!=0)
t=p[i-1].ct;
else
t=p[i].at;
b=p[i].bt;
for(j=i;j<n;j++) {
if((p[j].at<=t)&&(p[j].bt<=b)) {
pos=j;
b=p[i].bt;
}
}
p[pos].ct=t+p[pos].bt;
p[pos].tt=p[pos].ct-p[pos].at;
p[pos].wt=p[pos].tt-p[pos].bt;
sumwt+=p[pos].wt;
sumtt+=p[pos].tt;
temp=p[pos];
p[pos]=p[i];
p[i]=temp;
}
/*for(i=0;i<n;i++){
for(j=i+1;j<n;j++){
if(p[i].pno>p[j].pno){
temp=p[i];
p[i]=p[j];
p[j]=temp;
}
}
}*/
i=0;
printf("\nGANTT CHART\n%d",p[i].at);
for(i=0;i<n;i++){
printf("    P%d    %d",p[i].pno,p[i].ct);
}
printf("\n\nProcess no.\tArrival Time\tBurst time\tTurnarorund time\tWaiting time\n");
for(i=0;i<n;i++) {
printf("P%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",p[i].pno,p[i].at,p[i].bt,p[i].tt,p[i].wt);
}
printf("Average Turnaround time = %f\n",sumtt/n);
printf("Average Waiting time = %f\n",sumwt/n);
}
