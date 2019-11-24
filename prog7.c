#include<string.h>
#include<stdlib.h>
#include<stdio.h>
void S();
void A();
void B();
char input[100],output[100];
int i=0,error,j=0;
int main(){
    printf("Enter the input\n");
    gets(input);
 strcpy(output,"ASB");
printf("\n ASB");
 if(strlen(input)%2==0){
 printf("string rejected");
 return 1;
}
 if(input[strlen(input)/2]!='c'){
 printf("string rejected");
return 1;
}
    S();
       if(i==strlen(input)&&error==0){
    printf("String is accepted");
    return 1;}
else{
printf("string rejected");
}
}
void S(){

    if(input[i]=='c'){
 output[j]='c';
        printf("\n %s",output);
        i++;
        j++;
    }
    else
    {
     if(i==0)A();
     else {output[j]='A';output[j+1]='S';output[j+2]='B';output[j+3]='B';printf("\n %s",output);A();}
     S();
     B();
    }
}
void A(){
    if(input[i]=='a'){
        output[j]='a';
        printf("\n %s",output);
        i++;
        j++;
    }
    else
    {
        error=1;
    }
}
void B(){
    if(input[i]=='b'){
 output[j]='b';
        printf("\n %s\n",output);
        i++;
        j++;
    }
    else{
        error=1;
        }
}
