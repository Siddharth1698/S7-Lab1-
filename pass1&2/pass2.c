#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

FILE *fint,*ftab,*flen,*fsym,*fout,*ftemp;
int op1[10],txtlen,txtlen1,i,j=0,len,wordcount;
char add[5],symadd[5],op[5],start[10],temp[30],line[20],label[20],mne[10],operand[10],symtab[10],opmne[10];

void threeword(){
fscanf(fint,"%s%s%s%s",add,label,mne,operand);
if((strcmp(mne,"BYTE")==0)||(strcmp(mne,"WORD")==0))
{
if(strcmp(mne,"WORD")==0)
fprintf(fout,"0000%s^",operand);
else
{
len=strlen(operand);
for(i=2;i<len;i++)
{
fprintf(fout,"%d",operand[i]);
}
fprintf(fout,"^");
}
}
}
void twoword(){
fscanf(fint,"%s%s%s",add,mne,operand);
ftab=fopen("optab.txt","r");
fseek(ftab,SEEK_SET,0);
fsym=fopen("symtab.txt","r");
fseek(fsym,SEEK_SET,0);
if(strcmp(mne,"END")!=0)
{
fscanf(ftab,"%s%s",opmne,op);
while(!feof(ftab))
{
if(strcmp(mne,opmne)==0)
{
fclose(ftab);
fscanf(fsym,"%s%s",symadd,symtab);
while(!feof(fsym))
{
if(strcmp(operand,symtab)==0)
{
fprintf(fout,"%s%s^",op,symadd);
fclose(fsym);
break;
}
else
fscanf(fsym,"%s%s",symadd,symtab);
}
break;
}
else
fscanf(ftab,"%s%s",opmne,op);
}
}
else
fprintf(fout,"\nE^00%s",start); 
}

int main()
{
char ch;
fint=fopen("input2.txt","r");
flen=fopen("length.txt","r");
fout=fopen("machinecode.txt","w");
ftemp=fopen("input2.txt","r");

fscanf(fint,"%s%s%s",label,mne,operand);
if(strcmp(mne,"START")==0)
{
strcpy(start,operand);
fscanf(flen,"%d",&len);
}
fprintf(fout,"H^%s^%s^%d\nT^00%s^",label,start,len,start);
fgets(temp,25,ftemp);
while(!feof(fint)){
    wordcount=0;
    
    fseek(ftemp,7,SEEK_CUR);
    
   ch=getc(ftemp);
    if(ch=='\t')
    wordcount=2;
    else
    wordcount=3;
    fgets(temp,25,ftemp);
    switch(wordcount){
        case 3:threeword();
        break;
        case 2:twoword();
        break;
        default:
        break;
    }   
}


fclose(fint);
fclose(ftab);
fclose(fsym);
fclose(flen);
fclose(fout);
return 0;
}
