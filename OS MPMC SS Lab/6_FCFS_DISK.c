#include<stdio.h>
#include<stdlib.h>
void main() 
{
int i,n,req[10],head,hd,move=0;
printf("Enter the no. of requests : ");
scanf("%d",&n);
printf("Enter the current head position : ");
scanf("%d",&head);
hd=head;
printf("Enter the requests : ");
for(i=0;i<n;i++)
    scanf("%d",&req[i]);
for(i=0;i<n;i++) {
    move+=abs(head-req[i]);
    head=req[i];
}
printf("\nThe sequence is : %d",hd);
for(i=0;i<n;i++)
    printf(" -> %d",req[i]);
printf("\nTotal head movement is : %d\n",move);
}