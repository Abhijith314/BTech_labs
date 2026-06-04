#include<stdio.h>
void main() {
int i,j,k=0,f,n,s=-1,m=0,temp=0,o;
printf("Enter the number of reference string : ");
scanf("%d",&n);
printf("Enter the no. of frames : ");
scanf("%d",&f);
int ref[n],p[f];
printf("Enter the reference string : ");
for(i=0;i<n;i++)
scanf("%d",&ref[i]);   
for(i=0;i<f;i++)
p[i]=-1;
for(i=0;i<n;i++){
int a=ref[i];
int e=f-1;
m=0;
for(o=0;o<f;o++) {
if(a==p[o]) {
temp++;
}
}
if (temp!=0) {
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
if(s==e)
s=0;
else 
s++;
p[s]=a;
for(j=0;j<f;j++) {
if(p[j]==-1)
printf("-  ");
else
printf("%d  ",p[j]);
}
printf("\n");
k++;
}
}
printf("\nPage fault = %d\n", k);
}
