#include <stdio.h>
void main() {
int i,j,k=0,f,n,s=-1,m=0,temp=0,o;
printf("Enter the number of reference strings: ");
scanf("%d",&n);
printf("Enter the number of frames: ");
scanf("%d",&f);  
int ref[n],p[f],counter[f];
printf("Enter the reference string: ");
for(i=0;i<n;i++)
scanf("%d",&ref[i]);
for(i=0;i<f;i++) {
p[i]=-1;
counter[i]=0;
}
for(i=0;i<n;i++) {
int a=ref[i];
int e=f-1;
m=0;
for(o=0;o<f;o++) {
if(a==p[o]) {
temp++;
counter[o]=k+1;
}
}
if(temp!= 0) {
temp=0;
m=1;
}
printf("%d : ",ref[i]);
if(m==1) {
for(j=0;j<f;j++)
printf("%d  ",p[j]);
printf("\n");
}
else {
int min_count=counter[0];
int min_index=0;
for (j=1;j<f;j++) {
if (counter[j]<min_count) {
min_count=counter[j];
min_index=j;
}
}
p[min_index]=a;
counter[min_index]=k+1;
for(j=0;j<f;j++) {
if (p[j]==-1)
printf("-  ");
else
printf("%d  ", p[j]);
}
printf("\n");
k++;
}
}
printf("\nPage fault = %d\n", k);
}
