#include<stdio.h>
#include<string.h>


void bingo(char input[50],char output[50] )
	{
	char current[50];
	int i,p,j;
       //	printf("%s%s\n",input,output);
	for(i=0;i<=(strlen(input));i++)
		{
		while(output[i]=='A'||output[i]=='S'||output[i]=='B')
		{
	       //	printf(",output array of i= %c\n",output[i]);
		if(output[i]=='A')
		output[i]='a';
		else if(output[i]=='B')
		output[i]='b';
		else if(output[i]=='S')
			{
			if(input[i]=='c')
				{
				output[i]='c';
				//i++;
				}
			else if(input[i]!='a')
				{
			       //	printf("Not of the same kind\n");
				break;
				}
			else
				{
				strcpy(current,output);
			       //	printf("Current=%s",current);
				j=0;
				while(j<i)
					{
					output[j]=current[j];
					j++;
					p=j+1;
					}
				output[j]='A';
				output[j+1]='S';
				output[j+2]='B';
				for(j=j+3;j<=(strlen(input));j++)
					{
					output[j]=current[p];
					p++;
					}
				}
			}
		else
			{
			//printf("Not a type of this grammer\n");
			break;
			}
		printf("%s\n",output);
		}
		}

	if(strcmp(input,output)==0)
		printf("The input string is accepted\n");
	else
		printf("String is not accepted\n");
	}


void main()
	{
	char input[50],output[50],current[50];
	int i,j;//count=0;
	printf("Enter the String:");
	scanf("%s",input);

	strcpy(output,"S");
	printf("%s\n",output);
	if(input[0]=='c'&&input[1]==NULL)
		{
		printf("c\n");
		printf("The input string is accepted\n");
		}
	else
		{
		strcpy(output,"ASB");
		printf("%s\n",output);
		bingo(input,output);
		}
	}







