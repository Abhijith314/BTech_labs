#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(){
FILE *f1,*f2,*f3,*f4,*f5;
int i,pos=1,len;
char pos1[10],pos2[10],la[10],mne[10],opnd[10],mne1[10],opnd1[10],name[10],arg[10];
f1=fopen("input.txt","r");
f2=fopen("nametab.txt","w+");
f3=fopen("deftab.txt","w+");
f4=fopen("argtab.txt","w+");
f5=fopen("outmacro.txt","w+");
fscanf(f1,"%s %s %s",la,mne,opnd);
while(strcmp("END",la)!=0) {
    if(strcmp("MACRO",mne)==0) {
    fprintf(f2,"%s",la);
    rewind(f2);
    fprintf(f3,"%s\t%s\n",la,opnd);
    fscanf(f1,"%s%s%s",la,mne,opnd);
    while(strcmp(mne,"MEND")!=0) {
        if(opnd[0]=='&'){
            sprintf(pos1,"%d",pos);
            strcpy(pos2,"?");
            strcpy(opnd,strcat(pos2,pos1));
            pos++;
        }
        else {
            fprintf(f3,"%s\t%s\n",mne,opnd);
        }
        fprintf(f3,"%s\t%s\n",mne,opnd);
        fscanf(f1,"%s%s%s",la,mne,opnd);
    }
    fprintf(f3,"%s",mne);
    }
    else{
        rewind(f2);
        fscanf(f2,"%s",name);
        if(strcmp(name,mne)==0){
            printf("%s\n",opnd);
            len=strlen(opnd);
            for(i=0;i<len;i++){
                if(opnd[i]!=','){
                    fprintf(f4,"%c",opnd[i]);
                    printf("%c\n",opnd[i]);
                }
                else{
                    fprintf(f4,"\n");
                }
            }
            rewind(f3);
            rewind(f4);
            fscanf(f3,"%s %s",mne1,opnd1);
            fprintf(f5,".\t%s\t%s\n",mne1,opnd);
            fscanf(f3,"%s %s",mne1,opnd1);
            while(strcmp(mne1,"MEND")!=0) {
                if(opnd1[0]=='?'){
                    fscanf(f4,"%s",arg);
                    fprintf(f5,"-\t%s\t%s\n",mne1,arg);
                }
                else {
                    fprintf(f5,"-\t%s\t%s\n",mne1,arg);
                }
                fscanf(f3,"%s %s",mne1,opnd1);
            }
        }
        else{
            fprintf(f5,"%s\t%s\t%s\n",la,mne,opnd);
        }
    }
    fscanf(f1,"%s%s%s",la,mne,opnd);
}
fprintf(f5,"%s",la);
fclose(f1);
fclose(f2);
fclose(f3);
fclose(f4);
fclose(f5);
}
