#include<stdio.h>
struct process {
int pno,bt,cbt,tat,wt,at;
};
void main()
{
int n,i,tq,j;
float ttat,twt,atwt,atat;
printf("Enter the number of process : ");
scanf("%d",&n);
struct process p[n],temp;
printf("Enter the Process no., Arrival time and Burst time of :-\n");
for(i=0;i<n;i++) {
printf("Process : ");
scanf("%d %d %d",&p[i].pno,&p[i].at,&p[i].bt);
p[i].cbt=p[i].bt;
}
printf("Enter the time quantum : ");
scanf("%d",&tq);
for(i=0;i<n-1;i++) {
	for(j=i+1;j<n;j++) {
		if(p[i].at>p[j].at) {
			temp=p[i];
			p[i]=p[j];
			p[j]=temp;
		}
	}
}
printf("GANTT CHART\n0");
int time=0,completedp=0,t,queue[20],nxt,pro;
i=0,j=0;
do {
	if(p[i].bt>0  && p[i].at<=time) {
		if(p[i].bt>tq) {
			//queue[j]=i;
			queue[j]=p[i].pno;
			printf("%d   P%d\n",j,queue[j]);
			j++;
			time=time+tq;
			p[i].bt-=tq;
			//printf("  P%d  %d",p[i].pno,time);
			pro=i;
			for (t=j; t<time; t++) {
				if (p[(pro+1)%n].at<=t) {
					//queue[j]=(i+1)%n;
					queue[j]=p[(pro+1)%n].pno;
					printf("%d  iP%d  %d  %d  %d\n",j,queue[j],i,pro,t);
					j++;
					pro++;
				}
				else {
					//queue[j]=i;
					queue[j]=p[i].pno;
					printf("%d  eP%d  %d  %d  %d\n",j,queue[j],i,pro,t);
					j++;
					pro++;
				}
			}
		}
		else {
			time=time+p[i].bt;
			p[i].tat=time;
			p[i].wt=p[i].tat-p[i].cbt;
			p[i].bt=0;
			completedp++;
			//printf("  P%d  %d",p[i].pno,time);
			if(completedp==n) {
				break;
			}
		}
	}
	else {
	time=p[i].at;
    printf("  IDEAL  %d",time);
	}
	if(i==n-1) {
		i=0;
	}
	else {
		i++;
	}
scanf("%d",&nxt);
}while(nxt==1);
printf("\nProcess no.\tBurst time\tTurnaround time\tWaiting time\n");
for(i=0;i<n;i++) {
printf("P%d\t\t%d\t\t%d\t\t%d\n",p[i].pno,p[i].cbt,p[i].tat,p[i].wt);
}
ttat=p[n-1].tat;
twt=p[n-1].wt;
atat=ttat/n;
atwt=twt/n;
printf("Average Turnaround time = %f\n",atat);
printf("Average Waiting time = %f\n",atwt);
}
