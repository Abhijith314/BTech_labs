#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node {
char name[20];
struct node *next;
}*head=NULL,*temp=NULL,*list=NULL,*prev = NULL;
char dir[20];
int i,j,a;
void create();
void display();
int search();
void delete();
void main(){
int c;
printf("Enter the name of the directory : ");
scanf("%s",dir);
do{
printf("\n\t\tMENU\n\n1 : Create\n2 : Display\n3 : Search\n4 : delate\n5 : Exit\n");
printf("Enter the option : ");
scanf("%d",&c);
switch (c) {
case 1: create();
break;
case 2: display();
break;
case 3: search();
break;
case 4: delete();
break;
case 5: exit(0);
break;
}
}while(1);
}

void create() {
list=malloc(sizeof(struct node));
printf("Enter the name of file : ");
scanf("%s",list->name);
if(head==NULL) {
list->next=head;
head=list;
}
else {
temp=head;
while(temp->next!=NULL)
temp=temp->next;
temp->next=list;
list->next=NULL;
}
}
void display() {
temp=head;
printf("\nDirectory name : %s\n",dir);
if(head == NULL) 
printf("\nEmpty directory \n");
else {
printf("Files are :  ");
while(temp!=NULL) {
printf("%s ",temp->name);
temp=temp->next;
}
printf("\n");
}
}
int search() {
temp = head;
char ser[100];
printf("Enter the file name to search : ");
scanf("%s",ser);
for(i=0;temp!= NULL;i++) {
int a=strcmp(temp->name,ser);
if(a==0) {
printf("File '%s' has been found at position %d.\n",temp->name,i+1);
return 1;
}
temp=temp->next;
}
printf("File not found.\n");
return 0;
}
void delete() {
temp=head;
char del[100];
printf("Enter the file name to delete : ");
scanf("%s",del);
while(temp!=NULL) {
a=strcmp(temp->name,del);
if(a==0) {
if(temp==head){
printf("File %s has been deleted\n",temp->name);
if(temp->next==NULL)
head=NULL;
else 
head=head->next;
}
else {
printf("File '%s' has been deleted\n",temp->name);
prev->next=temp->next;
free(temp);
}
}
prev=temp;
temp=temp->next;
}
}
