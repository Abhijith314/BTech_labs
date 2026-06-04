#include<stdio.h>
struct process {
int pno,bt,rbt,tat,wt,at;
};
void main()
{
int n=4,i,tq=4,j,comp[n],tbt=0;
float ttat=0,twt=0,atwt,atat;
printf("Enter the number of process : %d",n);
//scanf("%d",&n);
struct process p[n],temp;
p[0].pno=1; p[0].at=2; p[0].bt=5;
p[1].pno=2; p[1].at=3; p[1].bt=8;
p[2].pno=3; p[2].at=0; p[2].bt=2;
p[3].pno=4; p[3].at=1; p[3].bt=9;
printf("\nEnter the Process no., Arrival time and Burst time of :-\n");
for(i=0;i<n;i++) {
printf("Process : %d %d %d\n",p[i].pno,p[i].at,p[i].bt);
//scanf("%d %d %d",&p[i].pno,&p[i].at,&p[i].bt);
p[i].rbt=p[i].bt;
tbt+=p[i].bt;
}
printf("Total burst time = %d\n",tbt);
printf("\nEnter the time quantum : %d\n",tq);
//scanf("%d",&tq);
for(i=0;i<n-1;i++) {
	for(j=i+1;j<n;j++) {
		if(p[i].at>p[j].at) {
			temp=p[i];
			p[i]=p[j];
			p[j]=temp;
		}
	}
}
/*printf("Sorted process structure:\n");
for ( i = 0; i < n; i++)
{
	printf("P%d %d %d\n",p[i].pno,p[i].at,p[i].bt);
}*/

for (i=0; i<n; i++)
comp[i]=-1;

//printf("GANTT CHART\n0");
int time=0,completedp=0,t,readyq[20],timeq[20],nxt,pro,k=0,flag=0,rqind=0,tmind=0,q;
//completedp:completed queue index; readyq:ready queue; timeq:time queue; pro:process index; 
//rqind:ready queue index; tmind:time queue index q:temp index for ready queue
i=0,j=0;
//queue[j]=i;
timeq[tmind]=0; tmind++;
readyq[j]=i;
printf("j%d   qP%d  tmq%d tmind%d\n",j,p[readyq[j]].pno,timeq[tmind-1],tmind);
j++;
do {
	if(p[i].rbt>0 || p[i].at<=time) {
		printf("before if(p[i].rbt>tq) time = %d  i=%d\n",time,i);
		if(p[i].rbt>tq) {
			
			//printf("before if(p[i].rbt>tq) time = %d\n",time);
			time=time+tq;
			timeq[tmind]=time; tmind++;
			printf("time%d  timeq%d  tmind%d\n",time,timeq[tmind-1],tmind);
			printf("if(p[i].rbt>tq) time = %d\n",time);
			p[i].rbt-=tq;
			printf(" ifExe P%d  rbt%d\n",p[i].pno,p[i].rbt);
			//printf("  P%d  %d\n",p[i].pno,time);
			//pro=i;
			//for(t=j,pro=i; t<=tbt; t++,pro++) {
			for(t=time,pro=i; t<tbt; t++) {
				/*for(k=0; k<n; k++) {	//loop to check the process is completed process
					if(comp[k]==(i+1)%n){
						flag=1;
						break;
					}
					else{
						flag=0;
					}
				}*/
				//if (p[(pro+1)%n].at<=time && flag!=1) {
				if (p[(pro+1)%n].at<=time && p[(pro+1)%n].rbt!=0 && readyq[j-1]!=(pro+1)%n) {
					//if(readyq[j]!=(pro+1)%n) {
						
						readyq[j]=(pro+1)%n;
						t=t+p[(pro+1)%n].bt;
						printf("%d   %d\n",readyq[j],(pro+1)%n);
					//}
					//queue[j]=(i+1)%n;
					printf("j%d  iqP%d  i%d  pr%d  t%d\n",j,p[readyq[j]].pno,i,(pro+1)%n,t);
					j++;
					pro++;
					//printf("afterIfTime = %d\n",time);
				}
			}
				
			//queue[j]=i;
			readyq[j]=i;
			printf("j%d  eqP%d  i%d  pr%d  t%d\n",j,p[readyq[j]].pno,i,(pro+1)%n,t);
			j++;
			pro++;
			printf("afetrIfTime = %d\n",time);
				
			
		}
		else {
			
			printf("lastExeElse time = %d  i=%d\n",time,i);
			time=time+p[i].rbt;
			timeq[tmind]=time; tmind++;
			printf("time%d  timeq%d  tmind%d\n",time,timeq[tmind-1],tmind);
			printf("processLastExeTime = %d\n",time);
			p[i].tat=time-p[i].at;
			p[i].wt=p[i].tat-p[i].bt;
			p[i].rbt=0;
			printf(" last Exe P%d  rbt%d\n",p[i].pno,p[i].rbt);
			comp[completedp]=i;
			completedp++;
			printf(" comp%d  %d i=%d  time=%d\n",completedp,p[i].pno,i,time);
			//printf("  P%d  %d",p[i].pno,time);
			for(t=time,pro=i; t<tbt; t++) {
				if (p[(pro+1)%n].at<=time && p[(pro+1)%n].rbt!=0 && readyq[j-1]!=(pro+1)%n) {
					//if(readyq[j]!=(pro+1)%n) {
						//printf("%d   %d\n",readyq[j],(pro+1)%n);
						readyq[j]=(pro+1)%n;
						t=t+p[(pro+1)%n].bt; 
					//}
					//queue[j]=(i+1)%n;
					printf("j%d  lsiqP%d  i%d  pr%d  t%d\n",j,p[readyq[j]].pno,i,(pro+1)%n,t);
					j++;
					pro++;
				}
				//pro++;
			}
			printf("lastfterIfTime = %d\n",time);
			if(completedp==n) {
				break;
			}
		}
		//if(i==n-1) {
		if(rqind==j-1) {
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
	
	printf("\n");
	for(q=0;q<j;q++)
	printf("%d  ",p[readyq[q]].pno);
	printf("\n\n");

	scanf("%d",&nxt);
}while(nxt==1);
printf("Total time = %d\n\nGANTT CHART\n%d  ",time,timeq[0]);
for(i=0,k=1;i<j,k<tmind;i++,k++)
printf("P%d  %d  ",p[readyq[i]].pno,timeq[k]);
printf("\n\nProcess no.\tBurst time\tArrival time\tTurnaround time\tWaiting time\n");
for(i=0;i<n;i++) {
printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pno,p[i].bt,p[i].at,p[i].tat,p[i].wt);
ttat+=p[i].tat;
twt+=p[i].wt;
}
//ttat=p[n-1].tat;
//twt=p[n-1].wt;
//atat=ttat/n;
//atwt=twt/n;
printf("Average Turnaround time = %f\n",ttat/n);
printf("Average Waiting time = %f\n",twt/n);
}
