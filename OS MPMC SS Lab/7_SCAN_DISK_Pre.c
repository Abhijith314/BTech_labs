#include<stdio.h>
#include<stdlib.h>
int head,pre,n,i,j,req[50],move=0,temp,size,hd;
void main()
{
    printf("Enter the current head position : ");
    scanf("%d",&head);
    size=200-1;
    printf("Enter the previous position : ");
    scanf("%d",&pre);
    printf("Enter the no. of request : ");
    scanf("%d",&n);
    printf("Enter the request : ");
    for(i=0;i<n;i++)
        scanf("%d",&req[i]);
    for(i=0;i<n;i++) {
        for (j=i+1;j<n;j++) {
            if(req[i]>req[j]) {
                temp=req[i];
                req[i]=req[j];
                req[j]=temp;
            }
        }
    }
    hd=head;
    if(pre<head){
        printf("The sequence is : %d",head);
        for (i=0;i<n;i++) {
            if (req[i]>=hd) {
                printf("->%d",req[i]);
                move+=abs(req[i]-head);
                head=req[i];
            }
        }
        printf("->%d",size);
        move+=abs(size-head);
        head=size;
        for (i=n-1;i>=0;i--) {
            if (req[i]<hd) {
                printf("->%d",req[i]);
                move+=abs(req[i]-head);
                head=req[i];
            }
        }
        printf("\n Total Head Movement = %d ",move);
    }
    else {
        printf("The sequence is : %d",head);
        for(i=n-1;i>=0;i--){
            if(req[i]<hd){
                printf("->%d",req[i]);
                move+=abs(req[i]-head);
                head=req[i];
            }
        }
        printf("->0");
        move+=abs(0-head);
        head=0;
        for (i=0;i<n;i++) {
            if (req[i]>=hd) {
                printf("->%d",req[i]);
                move+=abs(req[i]-head);
                head=req[i];
            }
        }
        printf("\n Total Head Movement = %d ",move);
    }
}
