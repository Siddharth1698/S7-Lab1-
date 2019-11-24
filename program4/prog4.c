#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For exit() function
int main()
{
    char c[1000]; int m;
    char ch,cp;
    FILE *fptr;
    if ((fptr = fopen("input.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }
   while(!feof(fptr)){
        fscanf(fptr,"%s",c);
        
   // printf("Data from the file:\n%s\n", c);
        
    for(int i = 0;i< strlen(c);i++){
		ch = c[i];
		
		
		switch(ch){
			  case 'i': 
			  
			    ch = c[++i];
			    if(ch == 'f'){
					 ch = c[++i];
					   if(ch == ' ' || ch == '('){
					     printf("keyword found: if");
					     printf("\n");
					   
					     } 
					}
				
					
				case 'd': 	
				  ch = c[++i];
			    if(ch == 'o'){
					 ch = c[++i];
					   if(ch == ' ' || ch == '(' || ch == '{'){
					     printf("keyword found: do");
					     printf("\n");
					     
					   } 
					}
			}
		}
	}
    fclose(fptr);
    
    return 0;
}
