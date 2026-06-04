#include<stdio.h>
#include<stdlib.h>
int head,pre,n,i,j,a[50],move,temp,size,hd;
void main()
{
  printf("Enter the current head position : ");
  scanf("%d",&head);
  printf("Enter the previous position : ");
  scanf("%d",&pre);
  size=200-1;
  printf("Enter the number of request : ");
  scanf("%d",&n);
  printf("Enter the request : ");
  for(i=0;i<n;i++) {
    scanf("%d",&a[i]);
  }
  for(i=0;i<n;i++) {
    for(j=0;j<n;j++) {
      if(a[i]<a[j]){
        temp=a[i];
        a[i]=a[j];
        a[j]=temp;
      }
    }
  }
  hd=head;
  if (pre<head)
  {
    printf("The sequence is : %d",head);
    for(i=0;i<n;i++) {
        if(a[i]>=hd) {
        printf(" -> %d",a[i]);
        move+=abs(a[i]-head);
        head=a[i];
        }
    }
    printf(" -> %d",size);
    move+=abs(size-head);
    head=size;
    for(i=n-1;i>=0;i--) {
        if(a[i]<hd) {
            printf(" -> %d",a[i]);
            move+=abs(a[i]-head);
            head=a[i];
        }
    }
    printf("\nTotal head movement = %d",move);
  }
  else{
    printf("The sequence is : %d",head);
    for(i=n-1;i>=0;i--) {
        if(a[i]<hd) {
            printf(" -> %d",a[i]);
            move+=abs(a[i]-head);
            head=a[i];
        }
    }
    printf(" -> 0");
    move+=abs(0-head);
    head=0;
    for(i=0;i<n;i++) {
        if(a[i]>=hd) {
        printf(" -> %d",a[i]);
        move+=abs(a[i]-head);
        head=a[i];
        }
    }
    printf("\nTotal head movement = %d",move);
  }
}
