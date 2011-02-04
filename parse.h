#ifndef _PARSE_H
#define _PARSE_H

/* See the documentation file for more information on this. */
#define SEPERATOR ":"
/* Macro which eleminates space from the buffer. */
#define REMOVE_SPACE(buffer,index){\
				    while((buffer[index]==' ' || buffer[index]=='\t')  && buffer[index]!='\0'){\
				    index ++;\
				    }\
				  }

/* The handle which is made for every distinct entry in the config file. */
typedef struct _h{
	const char *keyword;					/* Stores the name of the handler. */
	/* The parser will invoke the handler and pass value of the keyword to it. */ 
	int (*handler)(void *arg);			
	struct _h *next;
}Handler;

/* Structure which is used internally to keep track of handlers. */
typedef struct _h_table{
	const char *filename;				/* The name of the file to parse. */
	FILE *stream;
	Handler *first_handle;				/* Points to the first handle. */
}HandlerTable;

/* Function Prototypes. */
HandlerTable *Parser_Init(const char *filename);
void Parser_Close(HandlerTable *table);
int Parse_addHandler(const char *keyword,void *handler,HandlerTable *table);
int Parse_StartParser(HandlerTable *table);

#endif
