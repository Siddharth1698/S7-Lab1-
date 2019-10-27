
#include<stdio.h>
#include<stdlib.h>

FILE *f1,*f2,*f3,*f4,*f5,*f6;
int lc,sa,l,op1,o,len;
char m1[20],la[20],op[20],otp[20];

void threeword(){
fscanf(f1,"%s %s %s",la,m1,op);
 fprintf(f4,"\n%d\t%s\t%s\t%s\n",lc,la,m1,op);
 fprintf(f3,"\n%d\t%s\n",lc,la);
 f2=fopen("optab.txt","r");
 fscanf(f2,"%s %d",otp,&o);
 while(!feof(f2))
 {
  if(strcmp(m1,otp)==0)
  {
    lc=lc+3;
    break;
  }
  fscanf(f2,"%s %d",otp,&o);
  }
  fclose(f2);
  if(strcmp(m1,"WORD")==0)
 
    {
   lc=lc+3;
   }
   else if(strcmp(m1,"RESW")==0)
   {
    op1=atoi(op);
    lc=lc+(3*op1);
    }
    else if(strcmp(m1,"BYTE")==0)
    {
    if(op[0]=='X')
      lc=lc+1;
      else
      {
      len=strlen(op)-2;
      lc=lc+len;}
    }
    else if(strcmp(m1,"RESB")==0)
    {
     op1=atoi(op);
     lc=lc+op1;
     }
  
}
void twoword(){
    int found=0;
    fscanf(f1,"%s %s",m1,op);
 if(strcmp(m1,"END")!=0)
  fprintf(f4,"\n%d\t\t%s\t%s\n",lc,m1,op);
 
  
 f2=fopen("optab.txt","r");



 
  while(!feof(f2))
 {
   fscanf(f2,"%s %d",otp,&o);
  if(strcmp(m1,otp)==0)
  {
    found=1;
    lc=lc+3;
    break;
  }
  
  }
 
  
  fclose(f2);
  if(found==0){
     if(strcmp(m1,"END")==0){
              fprintf(f5,"Program length =\n%d",lc-sa);
              fprintf(f4,"\n%d\t\t%s\t\t\n",lc,m1);
              }
              else{
      printf("Invalid Operation");
      exit(EXIT_FAILURE);
              }
              }
              }

int main()
{
char ch,temp[100];
int wordcount=0,end=0;
f1=fopen("input.txt","r");
f4=fopen("input2.txt","w");
f3=fopen("symtab.txt","w");
f5=fopen("length.txt","w");
f6=fopen("input.txt","r");
fscanf(f1,"%s %s %d",la,m1,&op1);
if(strcmp(m1,"START")==0)
{
 sa=op1;
 lc=sa;
 fprintf(f4,"\t%s\t%s\t%d\n",la,m1,op1);
 }
 else
 lc=0;
fgets(temp,25,f6);
while(!feof(f1)){
  wordcount=0;
  ch=fgetc(f6);
  if(ch=='\t')
  wordcount=2;
  else
  wordcount=3;
  fgets(temp,25,f6);
  
             
             
              
              
  switch (wordcount)
     {
    case 3:
     threeword();
         break;
    case 2:
    twoword();
    break;
     
     default:
     
         break;
     }   
  }  
    


  
    fclose(f1);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    fclose(f6);
    }
