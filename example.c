#include <stdio.h>
#include "parse.h"

int pName(char *value);
int pEmail(char *value);
int pAddress(char *value);

int main(int argc,char *argv[]){
	/* Initialize the Parser datastructures */
	HandlerTable *table = Parser_Init("profile.conf");
	/* Add handlers to specific keywords. */
	Parser_addHandler("Name",pName,table);
	Parser_addHandler("Email",pEmail,table);
	Parser_addHandler("Address",pAddress,table);
	/* Start the parser. */
	Parser_StartParser(table);
	/* Clean up the parser data structures. */
	Parser_Close(table);

	return 0;
}

int pName(char *value){
	printf("Name : %s\n",value);
	
	return 0;
}

int pEmail(char *value){
	int flag = 0,index = 0;

	while(value[index]!='\0'){
		if(value[index]=='@')flag = 1;
		index ++;
	}
	if(!flag)
		printf("The email id does not contain @. Invalid\n");
	else
		printf("Email : %s\n",value);

	return 0;
}	

int pAddress(char *value){
	printf("Address : %s\n",value);

	return 0;
}
