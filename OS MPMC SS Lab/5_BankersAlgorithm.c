#include <stdio.h>
void main()
{
    int n,m,i,j,k;
    printf("Enter the number of processes and resources : ");
    scanf("%d %d",&n, &m);
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
    printf("The need matrix is :-\n");
    for(i=0;i<n;i++) {
        printf("P%d : ",i);
        for(j=0;j<m;j++) {
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }
    int y=0,flag;
    for(k=0;k<n;k++)  {
        for(i=0;i<n;i++) {
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


/*
OUTPUT

Enter the number of processes and resources : 5 3
Enter the allocation matrix for each process :
P0 : 0 1 0
P1 : 2 0 0 
P2 : 3 0 2
P3 : 2 1 1
P4 : 0 0 2
Enter the maximum matrix for each process :
P0 : 7 5 3
P1 : 3 2 2
P2 : 9 0 2
P3 : 2 2 2
P4 : 4 3 3
Enter the available resources : 3 3 2
The need matrix is :-
P0 : 7 4 3
P1 : 1 2 2
P2 : 6 0 0
P3 : 0 1 1
P4 : 4 3 1

Following is system is safe and the SAFE Sequence is :
P1 -> P3 -> P4 -> P0 ->  P2
*/