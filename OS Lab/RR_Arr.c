#include<stdio.h>
struct process {
int pno,bt,at,cbt,tat,wt;
};
void main()
{
int n,i,j,tq;
float ttat,twt,atwt,atat;
printf("Enter the number of process : ");
scanf("%d",&n);
struct process p[n],temp;
printf("Enter the Process no. Arrival time and Burst time of :-\n");
for(i=0;i<n;i++){
printf("Process %d : ",i);
scanf("%d %d %d",&p[i].pno,&p[i].at,&p[i].bt);
p[i].cbt=p[i].bt;
}
printf("Enter the time quantum : ");
scanf("%d",&tq);
for(i=0;i<n-1;i++){
for(j=i+1;j<n;j++){
if(p[i].at>p[j].at){
temp=p[i];
p[i]=p[j];
p[j]=temp;
}
}
}
/*printf("Sorted array is : \n");
for(i=0;i<n;i++) {
printf("%d %d %d\n",p[i].pno,p[i].at,p[i].bt);
}*/
printf("\nGANTT CHART\n0");
int x=0,y=0,t=0;
i=0;
while(1) {
	if(p[i].at<=t) {
		if(p[i].bt>0) {
			if(p[i].bt>tq) {
				x=x+tq;
				p[i].bt-=tq;
				printf("  P%d  %d",p[i].pno,x);
				t+=tq;
				}
			else {
				x=x+p[i].bt;
				p[i].tat=x;
				p[i].wt=p[i].tat-p[i].cbt;
				p[i].bt=0;
				y++;
				printf("  P%d  %d",p[i].pno,x);
				t+=tq;
				if(y==n){
					break;
					}
				}
		}
		if(i==n-1) {
			i=0; }
		else {
			i++; }
	
}
	else {
	t=p[i].at;
	}
}
printf("\n\nProcess no.\tArrival time\tBurst time\tTurnaround time\tWaiting time\n");
for(i=0;i<n;i++) {
printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pno,p[i].at,p[i].cbt,p[i].tat,p[i].wt);
}
ttat=p[n-1].tat;
twt=p[n-1].wt;
atat=ttat/n;
atwt=twt/n;
printf("Average Turnaround time = %f\n",atat);
printf("Average Waiting time = %f\n",atwt);
}
