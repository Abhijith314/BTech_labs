#include<stdio.h>
struct data
{
int p_no,bt_tm,arr,tat,wt,taat;
}a[20],temp;
void main()
{
int i,j,n;
float atat,awt,tta=0,tat=0,taat=0,twt,ttat=0;
printf("enter the no of process:");
scanf("%d",&n);
printf("enter the process number and burst time");
for(i=0;i<n;i++)
{
scanf("%d%d",&a[i].p_no,&a[i].bt_tm);
}
printf("enter the arrival time:");
for(i=0;i<n;i++)
{
scanf("%d",&a[i].arr);
}
for(i=0;i<n;i++)
{
for(j=i+1;j<n;j++)
{
if(a[i].arr>a[j].arr)
{
temp=a[i];
a[i]=a[j];
a[j]=temp;
}}}
for(i=0;i<n;i++)
{
//a[i].tat=tta+a[i].bt_tm;
tta=tta+a[i].bt_tm;
a[i].taat=tta-a[i].arr;
ttat=ttat+a[i].taat;
}
for(i=0;i<n;i++)
{
a[i].wt=a[i].taat-a[i].bt_tm;
twt=twt+a[i].wt;
}
atat=ttat/n;
awt=twt/n;
printf("prono\tarrivaltime\tbursttime\tturnaroundtime\twaitingtime\n");
for(i=0;i<n;i++)
{
printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",a[i].p_no,a[i].arr,a[i].bt_tm,a[i].taat,a[i].wt);
}
printf("the average turnaround time:%f\n",atat);
printf("the average waiting time:%f\n",awt);
printf("GANTT CHART\n");
printf("0");
for(i=0;i<n;i++)
{
printf("p%d\t%d",a[i].p_no,a[i].taat+a[i].arr);
}
printf("\n");
}
