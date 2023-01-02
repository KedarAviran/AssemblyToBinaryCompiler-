
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversion.h"
#define MAXDATA 80

struct Node
{
	char data[MAXDATA];
	char number[MAXDATA];
	char args[MAXDATA];
	struct Node* next;
}; 

/* gets and sets*/
char* getArgs(struct Node* node)
{
	if (*(node->args) == '\n')
		return NULL;
	return node->args;
}
void setArgs(struct Node* node, char arg[])
{
	strcpy(node->args, arg);
}
char* getNumber(struct Node* node)
{
	if (*(node->number) == '\n')
		return NULL;
	return node->number;
}
void setNumber(struct Node* node , int num)
{
        sprintf(node->number, "%d", num); 
}
struct Node* getNext(struct Node* node)
{
	return node->next;
}
void setNext(struct Node* node , struct Node* data)
{
	node->next = data;
}
char* getData(struct Node* node)
{
        char* format;
        format=(char*)malloc(82);
        format=removeSpaces(node->data);
        if(format==NULL)
                return NULL;
	if (*(format) == '\n')
		return NULL;
	return format;
}
/* returns the node if exsists in node chain witn data else null*/
struct Node* isExist(struct Node* node , char data[])
{
	while (node != NULL)
	{
		if (strcmp(node->data, data) == 0)
			return node;
		node = node->next;
	}
	return NULL;
}
/* return a new node with data*/
struct Node* createNode(char data[])
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	strcpy(new_node->data, data);
	new_node->next = NULL;
	return new_node;
}
/* adds new node after "from" with new data*/
struct Node* push(struct Node* from, char new_data[])
{
	struct Node* new_node = createNode(new_data);
	if (from != NULL)
	{
		if (from->next != NULL)
			new_node->next = from->next;
		from->next = new_node;
	}
	return new_node;
}
/* returns a copy of a node*/
struct Node* copy(struct Node* copy)
{
	struct Node* head = createNode(copy->data);
	struct Node* first = head;
	while (copy->next!=NULL)
	{
		head->next = createNode((copy->next)->data);
		head = head->next;
		copy = copy->next;
	}
	return first;
}
/* conjoin 2 nodes to 1 list*/
void conjoin(struct Node* to , struct Node* from)
{
	struct Node* last = to->next;
	to->next = from;
	while (from->next!=NULL)
		from = from->next;
	from->next = last;
}
/* prints list for debugging*/
void printList(struct Node* node)
{
	while (node!=NULL)
	{
		printf("%s",node->data);
		node = node->next;
	}
}
/* prints list with new line for debugging*/
void printListNewLine(struct Node* node)
{
	while (node != NULL)
	{
		printf("%s\n",node->data);
		node = node->next;
	}
}
/* loads code from given location to list, skips ;*/
struct Node* loadCodeFromFile(char src[])
{
	struct Node* first;
        struct Node* head;
	FILE* fp;
	char buff[MAXDATA];
	char* check;
	fp = fopen(src, "r");
	first = push(NULL,"");
	head= first;
	while (fgets(buff, MAXDATA, (FILE*)fp) != NULL)
	{
		check = removeSpaces(buff);
		if (check != NULL)
			if (check[0] != ';')
				head = push(head, buff);
	}
	fclose(fp);
	first = first->next;
	return first;
}
