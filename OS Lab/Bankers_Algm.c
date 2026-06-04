#include <stdio.h>
void main()
{
int n,m,i,j,k;
printf("Enter the number of processes : ");
scanf("%d",&n);
printf("Enter the number of resources : ");
scanf("%d",&m);
int allocation[n][m], maximum[n][m], available[m];
printf("Enter the allocation matrix for each process :\n");
for(i=0;i<n;i++) {
printf("P%d : ",i);
for(j=0;j<m;j++) {
scanf("%d",&allocation[i][j]);
}
}
printf("Enter the maximum matrix for each process :\n");
for(i=0;i<n;i++) {
printf("P%d : ",i);
for(j=0;j<m;j++) {
scanf("%d",&maximum[i][j]);
}
}
printf("Enter the available resources : ");
for(k=0;k<m;k++) 
scanf("%d",&available[k]);
int finish[n],ans[n],ind=0,need[n][m];
for(k=0;k<n;k++) 
finish[k]=0;
for(i=0;i<n;i++) {
for(j=0;j<m;j++) {
need[i][j] = maximum[i][j]-allocation[i][j];
}
}
int y=0,flag;
for(k=0;k<n;k++) 
for(i=0;i<n;i++) 
if(finish[i]==0) {
flag=0;
for(j=0;j<m;j++) 
if(need[i][j]>available[j]) {
flag=1;
break;
}
if(flag==0) {
ans[ind++]=i;
for(y=0;y<m;y++)
available[y] += allocation[i][y];
finish[i]=1;
}
}
flag = 1;
for(i=0;i<n;i++) {
if(finish[i]==0) {
flag=0;
printf("\nThe following system is not safe\n");
break;
}
}
if(flag==1) {
printf("\nFollowing is system is safe and the SAFE Sequence is :\n");
for(i=0;i<n-1;i++)
printf("P%d -> ",ans[i]);
printf(" P%d\n",ans[n-1]);
}
}
