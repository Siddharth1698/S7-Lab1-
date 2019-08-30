#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

//***********

struct token
{
char type[30];
char name[50];
int id;
}retToken;

//*******

struct symboltable
{
char type[30];
char name[50];
}st[60];

typedef struct token token;

char* sourcecode;
int lexbeg=0,fwdptr=0,state=0;
int symbolcount=0;
token newtoken;
int isexist=0,lineno=1;

//************

int indexof(char *subString,int fromIndex,char *MainString)
{
	int Mainlength,subLength,i,j,retIndex=-1;
	Mainlength=strlen(MainString);
	subLength=strlen(subString);
	if(Mainlength<1||subLength<1||Mainlength-fromIndex<subLength)
		return(-1);
	for(i=fromIndex;Mainlength-i>=subLength;i++)
		{
		if(*(MainString+i)==*(subString))
			{
			retIndex=i;
			for(j=0;j<subLength;j++)
				{
				if(*(MainString+i+j)!=*(subString+j))
					{
					retIndex=-1;
					break;
					}
				}
			if(retIndex!=-1)
				return retIndex;
			}
		}
	return (-1);
}

//************

char * subString(char *MainString,int fromIndex,int toIndex)
{
int Mainlength,j;
char *subStr;
Mainlength=strlen(MainString);
if(fromIndex<0||fromIndex>=Mainlength||toIndex<fromIndex||toIndex>=Mainlength)
	{
	printf("\nError in args: subString fn");
	return(NULL);
	}
subStr=(char *)malloc(1000*sizeof(char));
for(j=0;j<=toIndex-fromIndex;j++)
	*(subStr+j)=*(MainString+fromIndex+j);

*(subStr+j)='\0';
return(subStr);
}

//************

char nextchar()
{
fwdptr++;
return(sourcecode[fwdptr-1]);
}

//************

void retract(int n)
{
fwdptr-=n;
}

//************

int fail(char * msg)
	{
	printf("%s",msg);
	return(-1);
	}

//************

int installid(char *string)
{
int i;
for(i=0;i<symbolcount;i++)
{
if(strcmp(string,st[i].name)==0)
	return i;
}
strcpy(st[symbolcount].name,string);
strcpy(st[symbolcount].type,"identifier");
symbolcount++;
return(symbolcount-1);
}

//************

token getType(char *tok)
{
int i;
token tt;
for(i=0;i<symbolcount;i++)
	{
	if(strcmp(st[i].name,tok)==0)
		{
        strcpy(tt.type,st[i].type);
        strcpy(tt.name,st[i].name);
        tt.id=i;
		return(tt);
		}
	}

}

//************

int isSymbol(char c)
{
int i;
char syms[]={'.','<','>',',','{','}','(',')','#',';'};
for(i=0;i<10;i++)
{
if(c==syms[i])
	return(i+41);
}
return(0);
}

void nextToken()
{
char c;
char *temptok;
state=0;
while(*(sourcecode+fwdptr)!='\0'&&state!=-1)
{
switch(state)
	{
	case -1:return;
	case 0:c=nextchar();
		if(c==' '||c=='\t'||c=='\n')
			{
			state=0;
			lexbeg++;
			if(c=='\n')
				{
				lineno++;
				printf("\nline %d: ",lineno);
				}
			if(c=='\0')
				state=-1;
			}
		else if(c=='<')
			state=1;
		else if(c=='>')
			state=5;
		else if(c=='=')
			state=8;
		else if(isalpha(c))
			state=10;
		else if(isdigit(c))
			state=22;
		else if(isSymbol(c))
			state=24;
		else if(c=='+')
			state=12;
		else if(c=='-')
			state=15;
		else if(c=='*')
			state=18;
		else if(c=='/')
			state=19;
		else if(c=='%')
			state=20;
		else
			state=fail("unknown symbol encountered");
		break;
	case 1:c=nextchar();
		if(c=='=')
			state=2;
		else if(c=='>')
			state=3;
		else
			state=4;
		break;
	case 2:strcpy(retToken.type,"relop");
		strcpy(retToken.name,"LE");
		retToken.id=17;lexbeg=fwdptr;return;
	case 3:strcpy(retToken.type,"relop");retToken.id=18;
		strcpy(retToken.name,"NE");lexbeg=fwdptr;return;
	case 4:retract(1);
		strcpy(retToken.type,"relop");retToken.id=19;
		strcpy(retToken.name,"LT");lexbeg=fwdptr;return;
	case 5:c=nextchar();
		if(c=='=')
			state=6;
		else
			state=7;
		break;
	case 6:strcpy(retToken.type,"relop");retToken.id=20;
		strcpy(retToken.name,"GE");lexbeg=fwdptr;return;
	case 7:retract(1);
		strcpy(retToken.type,"relop");retToken.id=21;
		strcpy(retToken.name,"GT");lexbeg=fwdptr;return;
	case 8:c=nextchar();
		if(c=='=')
			state=9;
		else
			state=21;
		break;
	case 9:strcpy(retToken.type,"relop");retToken.id=22;
		strcpy(retToken.name,"EQ");lexbeg=fwdptr;return;
	case 10:c=nextchar();
		if(isalpha(c)||isdigit(c))
			state=10;
		else
			state=11;
		break;
	case 11:retract(1);
		temptok=subString(sourcecode,lexbeg,fwdptr-1);
		retToken.id=installid(temptok);
		retToken=getType(temptok);
		lexbeg=fwdptr;return;
	case 12:c=nextchar();
		if(c=='+')
			state=13;
		else
			state=14;
		break;
	case 13:strcpy(retToken.type,"arop");retToken.id=23;
		strcpy(retToken.name,"INC");lexbeg=fwdptr;return;
	case 14:retract(1);
		strcpy(retToken.type,"arop");retToken.id=24;
		strcpy(retToken.name,"PLU");lexbeg=fwdptr;return;
	case 15:c=nextchar();
		if(c=='-')
			state=16;
		else
			state=17;
		break;
	case 16:strcpy(retToken.type,"arop");retToken.id=25;
		strcpy(retToken.name,"DEC");lexbeg=fwdptr;return;
	case 17:retract(1);
		strcpy(retToken.type,"arop");retToken.id=26;
		strcpy(retToken.name,"MIN");lexbeg=fwdptr;return;
	case 18:strcpy(retToken.type,"arop");retToken.id=27;
		strcpy(retToken.name,"MUL");lexbeg=fwdptr;return;
	case 19:strcpy(retToken.type,"arop");retToken.id=28;
		strcpy(retToken.name,"DIV");lexbeg=fwdptr;return;
	case 20:strcpy(retToken.type,"arop");retToken.id=29;
		strcpy(retToken.name,"MOD");lexbeg=fwdptr;return;
	case 21:retract(1);retToken.id=30;
		strcpy(retToken.type,"arop");
		strcpy(retToken.name,"ASSIGN");lexbeg=fwdptr;return;
	case 22:c=nextchar();
		if(isdigit(c))
			state=22;
		else
			state=23;
		break;
	case 23:retract(1);retToken.id=41;
		strcpy(retToken.type,"Numeric constant");
		strcpy(retToken.name,subString(sourcecode,lexbeg,fwdptr-1));lexbeg=fwdptr;return;
	case 24:strcpy(retToken.type,"Reserved Symbol");retToken.id=isSymbol(c);
		strcpy(retToken.name,subString(sourcecode,lexbeg,fwdptr-1));lexbeg=fwdptr;return;

	}
}

}

//************

void regkeywords()
{
int i;
char keywords[][15]={"do","while","main","for","include","if","else","break","continue","int","char","float","double","void","return","switch","case"};
//17
char relop[][3]={"LE","NE","LT","GE","GT","EQ"};//17 to 22
char arop[][7]={"INC","PLU","DEC","MIN","MUL","DIV","MOD","ASSIGN"};//23 to 30
char syms[][2]={".","<",">",",","{","}","(",")","#",";"};//31 to 40

for(i=0;i<=16;i++)
{
strcpy(st[i].name,keywords[i]);
strcpy(st[i].type,"keyword");
}

for(i=17;i<=22;i++)
{
strcpy(st[i].name,relop[i-17]);
strcpy(st[i].type,"relop");
}

for(i=23;i<=30;i++)
{
strcpy(st[i].name,arop[i-23]);
strcpy(st[i].type,"arop");
}

for(i=31;i<41;i++)
{
strcpy(st[i].name,syms[i-31]);
strcpy(st[i].type,"Reserved Symbol");
}
strcpy(st[41].name,"NC");
strcpy(st[41].type,"Numeric Constant");
symbolcount=42;

}

//************

void main()
{
int i;
char c,*line;
FILE *input;
input=fopen("input.c","r");
i=0;
sourcecode=(char*)malloc(sizeof(char)*1200);
while((c=getc(input))!=EOF)
	{
	*(sourcecode+i)=c; i++;
	}
*(sourcecode+i)='\0';
regkeywords();
printf("\nline 1: ");
nextToken();
while(state!=-1)
{
printf("type: %s, name: %s, id= %d\n",retToken.type,retToken.name,retToken.id);
nextToken();
if(lexbeg>=strlen(sourcecode)||fwdptr>=strlen(sourcecode))
	state=-1;
}
printf("\nSymbol Table:\n");
for(i=0;i<=symbolcount;i++)
{
    printf("\nType: %s",st[i].type);
    printf("\tName: %s",st[i].name);
    printf("\tid=: %d",i);
}
}


