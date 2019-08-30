#include<stdlib.h>
 #include<stdio.h>
#include<string.h>
void chk_label();
void chk_opcode();
void READ_LINE();
struct optab
{
    char   code[10],objcode[10];
}myoptab[3]={
                   {"LDA","00"},
                   {"JMP","01"},
                   {"STA","02"}
             };
                   
                   
struct symtab{
                    char symbol[10];
                    int addr;
              }mysymtab[10];
                    
int startaddr,locctr,symcount=0,length;
char line[20],label[8],opcode[8],operand[8],programname[10];
                    
                void PASS1()
                  {
                       FILE *input,*inter;                                   
                       input=fopen("input.txt","r");                             
                       inter=fopen("inter.txt","w"); 
                        printf("LOCATION LABEL\tOPERAND\tOPCODE\n");
                        printf("_____________________________________");                       
                        fgets(line,20,input);
                      
                      READ_LINE();
                      
                     if(!strcmp(opcode,"START"))
                      {
                      
                       startaddr=atoi(operand); 
                       locctr=startaddr;                     
                      strcpy(programname,label);
                       
                           fprintf(inter,"%s",line);
                       fgets(line,20,input);
                       }
                      else
                      {
                          programname[0]='\0';
                          startaddr=0;
                          locctr=0;
                      }
                         printf("\n %d\t %s\t%s\t %s",locctr,label,opcode,operand);  
                          
                           while(strcmp(line,"END")!=0)
                          {
                   
                                   READ_LINE();
                                   printf("\n %d\t %s \t%s\t %s",locctr,label,opcode,operand);
                                   if(label[0]!='\0')chk_label();
                                   chk_opcode(); 
                                   fprintf(inter,"%s %s %s\n",label,opcode,operand);
                                   fgets(line,20,input);
                          }
                          
                   printf("\n %d\t\t%s",locctr,line);
                   fprintf(inter,"%s",line);
  
                    fclose(inter);
                    fclose(input);
                      }
//=====================================================================================================================================                      
        
//=================================================
 
       void READ_LINE()
       { 
            char buff[8],word1[8],word2[8],word3[8];
            int i,j=0,count=0;
             label[0]=opcode[0]=operand[0]=word1[0]=word2[0]=word3[0]='\0';
                 for(i=0;line[i]!='\0';i++)
                      {
                   if(line[i]!=' ')buff[j++]=line[i];
                   else
                      {
                     buff[j]='\0';
                     strcpy(word3,word2);strcpy(word2,word1);strcpy(word1,buff); 
                     j=0;count++;
                      }
                      }
                      buff[j-1]='\0';
                      strcpy(word3,word2);
                      strcpy(word2,word1); 
                      strcpy(word1,buff);
                    switch(count)
                       {
                                    case 0:strcpy(opcode,word1);break;
                                    case 1:{strcpy(opcode,word2);strcpy(operand,word1);}break;
                                    case 2:{strcpy(label,word3);strcpy(opcode,word2);strcpy(operand,word1);}break;
                       }
                       }
//======================================================
            void chk_label()
                  {
                       int k,dupsym=0;
                     for(k=0;k<symcount;k++)
                     if(!strcmp(label,mysymtab[k].symbol))
                     {
                                                          mysymtab[k].addr=-1;
                                                          dupsym=1;
                                                          break;
                                                          }
               if(!dupsym)
               {
               strcpy(mysymtab[symcount].symbol,label);
               mysymtab[symcount++].addr=locctr;
                }
                }
//  =====================================================     
  void chk_opcode()
         { 
                       
          int k=0,found=0;
          for(k=0;k<3;k++)
          
                    
                          if(!strcmp(opcode,myoptab[k].code))
                          {
                                                           
                                                     locctr+=3;
                                                   
                                                     found=1;
                                                     break;             
                           }
              if(!found)
              {
                        if(!strcmp( opcode,"WORD")) locctr+=3;
                        else if (!strcmp(opcode,"RESW"))locctr+=(3*atoi(operand));
                        else if(!strcmp(opcode,"RESB"))locctr+=atoi(operand);
               }
    }
            
//==================================================
  int main()
                    {
                     
                    
                        PASS1();
                        length=locctr-startaddr;
                        printf("\n The length is: %d", length);                                            

                    }     

