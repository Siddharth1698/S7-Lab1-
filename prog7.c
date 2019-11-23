#include<string.h>
#include<stdlib.h>
#include<stdio.h>
void S();
void A();
void B();
char input[100],output[100];
int i=0,error;
int main(){
    printf("Enter the input");
    gets(input);
 strcpy(output,"ASB");

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
 output[i]='c';
        printf("\n %s",output);
        i++;
    }
    else
    {
     A();
     S();
     B();   
    }
}
void A(){
    if(input[i]=='a'){
  output[i]='a';
        printf("\n %s",output);
        i++;   
    }
    else
    {
        error=1;
    }
}
void B(){
    if(input[i]=='b'){
 output[i]='b';
        printf("\n %s\n",output);
        i++;
    }
    else{
        error=1;
        }
}
