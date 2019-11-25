#include <string.h>
#include <stdio.h>
int main()
{
    char stack[100];
    char inp[100];
    char* input=inp;
    int stsize=0;
    char* stptr=stack+stsize;
    int update,i;
    printf("Enter the string: ");
    scanf("%s",inp);
    input[((int)strlen(input))+1]='\0';
    input[((int)strlen(input))+2]='\0';
    input[((int)strlen(input))]='$';
    stack[stsize++]='$';
    stack[stsize]='\0';
    printf("STACK\t\tINPUT\t\tACTION\n");
    while(strlen(input)!=0)
    {
        update=0;
            //check symbol matching grammar in stack for reduce
            char* stptr=stack+stsize-1;
            if(!(stack[stsize-1]=='T' && input[0]=='*')){
            for(i=(strlen(stack)-2);i>=0;i--)
            {
                if(strcmp((stptr-i),"E+T")==0)
                {
                    (stptr-i)[0]='E';
                    (stptr-i)[1]='\0';
                    stsize-=2;
                    update=1;
                    printf("\t\t\t\treduce E <- E+T\n");
                    break;

                }
                else if(strcmp((stptr-i),"T")==0)
                {
                    (stptr-i)[0]='E';
                    (stptr-i)[1]='\0';
                    update=1;
                    printf("\t\t\t\treduce E <- T\n");
                    break;
                }
                else if(strcmp((stptr-i),"T*F")==0)
                {
                    (stptr-i)[0]='T';
                    (stptr-i)[1]='\0';
                    stsize-=2;
                    update=1;
                    printf("\t\t\t\treduce T <- T*F\n");
                    break;

                }
                else if(strcmp((stptr-i),"F")==0)
                {
                    (stptr-i)[0]='T';
                    (stptr-i)[1]='\0';
                    update=1;
                    printf("\t\t\t\treduce T <- F\n");
                    break;

                }
                else if(strcmp((stptr-i),"(E)")==0)
                {
                    (stptr-i)[0]='F';
                    (stptr-i)[1]='\0';
                    stsize-=2;
                    update=1;
                    printf("\t\t\t\treduce F <- (E)\n");
                    break;

                }
                else if(strcmp((stptr-i),"id")==0)
                {
                    (stptr-i)[0]='F';
                    (stptr-i)[1]='\0';
                    stsize-=1;
                    update=1;
                    printf("\t\t\t\treduce F <- id\n");
                    break;

                }
            }}
            //shift if no reduce
            if(update==0 && input[0]!='$')
            {
                stack[stsize++]=input++[0];
                stack[stsize]='\0';
                update=1;
                printf("\t\t\t\tshift\n");
            }


            //check if accept state reached if no shift either
            if(update==0)
            {
                if(strcmp(input,"$")==0 && strcmp(stack,"$E")==0)
                {
                    printf("\nString Accepted\n");
                    return 0;
                }
                //if no action possible not accepted
                break;
            }
            printf("%s\t\t%s\t\t\n",stack,input);
    }
    printf("\nNo action possible. String not accepted\n");
    return 0;
}
