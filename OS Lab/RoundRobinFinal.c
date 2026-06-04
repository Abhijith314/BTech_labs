#include<stdio.h>
struct process {
int pno,bt,rbt,tat,wt,at;
};
void main()
{
int n=4,i,tq=3,j,tbt=0;
float ttat=0,twt=0;
printf("Enter the number of process : %d",n);
//scanf("%d",&n);
struct process p[n],temp;
p[0].pno=1; p[0].at=2; p[0].bt=2;
p[1].pno=2; p[1].at=5; p[1].bt=6;
p[2].pno=3; p[2].at=0; p[2].bt=4;
p[3].pno=4; p[3].at=4; p[3].bt=7;
printf("\nEnter the Process no., Arrival time and Burst time of :-\n");
for(i=0;i<n;i++) {
printf("Process : %d %d %d\n",p[i].pno,p[i].at,p[i].bt);
//scanf("%d %d %d",&p[i].pno,&p[i].at,&p[i].bt);
p[i].rbt=p[i].bt;
tbt+=p[i].bt;
}
printf("\nEnter the time quantum : %d\n",tq);
//scanf("%d",&tq);
for(i=0;i<n-1;i++) {		//sort the process structure using arrival time
	for(j=i+1;j<n;j++) {
		if(p[i].at>p[j].at) {
			temp=p[i];
			p[i]=p[j];
			p[j]=temp;
		}
	}
}

int time=0,completedp=0,t,readyq[20],timeq[20],nxt,pro,k=0,flag=0,rqind=0,tmind=0,q;
//completedp:completed queue index; readyq:ready queue; timeq:time queue; pro:process index; 
//rqind:ready queue index; tmind:time queue index q:temp index for ready queue
i=0,j=0;
timeq[tmind]=0;  tmind++;	//maintining time queue for GANTT CHART winth index tmind
readyq[j]=i;  j++;			//maintaing ready queue with index j
while(completedp<n) {
	if(p[i].rbt>0 || p[i].at<=time) {
		if(p[i].rbt>tq) {
			time=time+tq;
			timeq[tmind]=time; tmind++;
			p[i].rbt-=tq;
			for(t=time,pro=i; t<tbt; t++) {   //checking upcoming process is ready to execute
				if (p[(pro+1)%n].at<=time && p[(pro+1)%n].rbt!=0 && readyq[j-1]!=(pro+1)%n) {
					readyq[j]=(pro+1)%n;
					t=t+p[(pro+1)%n].bt;
					j++;
					pro++;
				}
			}
			readyq[j]=i;  //insert the current process in ready queue
			j++;
			pro++;
		}
		else {
			time=time+p[i].rbt;
			timeq[tmind]=time; tmind++;
			p[i].tat=time-p[i].at;
			p[i].wt=p[i].tat-p[i].bt;
			p[i].rbt=0;
			completedp++;
			for(t=time,pro=i; t<tbt; t++) {   //checking upcoming process is ready to execute
				if (p[(pro+1)%n].at<=time && p[(pro+1)%n].rbt!=0 && readyq[j-1]!=(pro+1)%n) {
					readyq[j]=(pro+1)%n;
					t=t+p[(pro+1)%n].bt; 
					j++;
					pro++;
				}
			}
		}
		if(rqind==j-1) {   //setting i with process index in readyq
			i=(i+1)%n;
		}
		else {
			rqind++;
			i=readyq[rqind];
		}
	}
	else {
	time=p[i].at;
    printf("  IDEAL  %d",time);
	}
}
printf("\nGANTT CHART\n%d  ",timeq[0]);   //printing GANTT CHART
for(i=0;i<j;i++)
printf("P%d  %d  ",p[readyq[i]].pno,timeq[i+1]);
printf("\n\nProcess no.\tBurst time\tTurnaround time\tWaiting time\n");
for(i=0;i<n;i++) {
printf("P%d\t\t%d\t\t%d\t\t%d\n",p[i].pno,p[i].bt,p[i].tat,p[i].wt);
ttat+=p[i].tat;
twt+=p[i].wt;
}
printf("Average Turnaround time = %f\n",ttat/n);
printf("Average Waiting time = %f\n",twt/n);
}
