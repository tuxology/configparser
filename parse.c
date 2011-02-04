
// ConfigParser
//--------------------------------------------------------------------------------
//
// Copyright (C) 2011 Shravan Aras <123.shravan@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 3 as published by
// the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
//---------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

/* Function to initialize all the parsing structures. */
/* Returns a pointer to the handler table which is the basic variable of the complete parser. */
/* Returns NULL if there is an error. */
HandlerTable *Parser_Init(const char *filename){
	HandlerTable *table = (HandlerTable*)malloc(sizeof(HandlerTable));		
	
	if(table==NULL)return NULL;
	table->filename = filename; 
	table->stream = fopen(filename,"r");
	table->first_handle = NULL;

	return table;
}

/* Does house keeping work. */
void Parser_Close(HandlerTable *table){
	Handler *handle;
	
	handle = table->first_handle;
	while(handle!=NULL){
		table->first_handle = table->first_handle->next;
		free(handle);
		handle = table->first_handle;
	}
	free(table);
}

/* Adds handlers to the handler table. */
/* Returns -1 on error. */
int Parser_addHandler(const char *keyword,void *handler,HandlerTable *table){
	Handler *current_handler;
	
	if(table==NULL)return -1;
	current_handler = (Handler*)malloc(sizeof(Handler));
	current_handler->keyword = keyword;
	current_handler->handler = handler;
	current_handler->next = table->first_handle;
	table->first_handle = current_handler;

	return 0;
}

/* To parse the file and call the handlers as an when required. */
/* This is a very rudimentary parser. I was running out of time handle error corrections here. */
int Parser_StartParser(HandlerTable *table){
	char buffer[512],keyword[64],value[448];
	int index = 0,key_index = 0,value_index = 0;
	Handler *handler;

	while(fgets(buffer,256,table->stream)!=NULL){
		key_index = 0;
		value_index = 0;
		index = 0;

		REMOVE_SPACE(buffer,index);
		while(buffer[index]!=':' && buffer[index]!='\0'){
			if(buffer[index]!=' ' && buffer[index]!='\t')	
				keyword[key_index++] = buffer[index];
			index ++;
		}
		keyword[key_index] = '\0';
		REMOVE_SPACE(buffer,index);
		index ++;
		while(buffer[index]!='\0'){
			if(buffer[index]!=' ' && buffer[index]!='\t'  && buffer[index]!=':'){
				value[value_index] = buffer[index];
				value_index ++;
			}
			index ++;
		}
		value[value_index] = '\0';

		/* Now that we have got the keyword and value pair we should check if there is a handler associated with it. */
		handler = table->first_handle;		
		while(handler!=NULL){
			if(strcmp(handler->keyword,keyword)==0){		/* Match is found call the function :) */
				/* Call the handler. */
				handler->handler(value);
			}
			handler = handler->next;
		}
	}	
	return 0;
}
