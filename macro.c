#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"
#define OUTLOC ".am"

/* createFileWithData at loc*/
void createFileWithData(struct Node* node, char* loc)
{
        struct Node* head;
	FILE* fptr;
	fptr = fopen(loc, "w");
	head = node;
	while (head != NULL)
	{
		char* str = getData(head);
		if (str == NULL)
			str = "\n";
		fprintf(fptr, "%s", str);
		head = getNext(head);
	}
	fclose(fptr);
}
/* remove Spaces and tabs from data*/
char* removeSpaces(char* data)
{
        int i;
	if (data == NULL)
		return NULL;
	i = 0;
	while (*(data+i) != '\0')
	{
		if (*(data + i) != ' ' && *(data + i) != '\t' && (int)(*(data + i)) != 13)
			return data + i;
		i++;
	}
	return data + i;
}
/* remove SlashN from data*/
char* removeSlashN(char* data)
{
	*(data + strlen(data)-1) = '\0';
        return data;
}
/* returns the node before the node that has the "key"*/
struct Node* findNextKeyword(struct Node* node, char key[])
{
	struct Node* head = node;
	while (head != NULL)
	{
		char* rest = NULL;
		struct Node* next = getNext(head);
		if (next != NULL && getData(next)!= NULL)
			rest = strstr(getData(next), key);
		if (rest != NULL)
			return head;
		head = getNext(head);
	}
	return NULL;
}
/* replace Macro name is macro name, info is macro lines, node is the cmds  */
void replaceMacro(char name[], struct Node* info , struct Node* node)
{
	struct Node* start;
	start = findNextKeyword(node, name);
	while (start != NULL)
	{
		struct Node* cont = getNext(getNext(start));
		setNext(start, cont);
		conjoin(start, copy(info));
		start = findNextKeyword(node, name);
	}
}
/* find macros and replace the keywords accordingly  */
void handleMacro(struct Node* node)
{
	struct Node* before;
        struct Node* end;
        struct Node* cont;
        struct Node* start;
        char* name;
	before = findNextKeyword(node, "macro");
	while (before != NULL)
	{
		start = getNext(before);
		name = strstr(getData(start), "macro") + 5;
		name = removeSpaces(name);
		name = removeSlashN(name);
		start = getNext(start);
		end = findNextKeyword(start, "endmacro");
		cont = getNext(getNext(end));
		setNext(end, NULL);
		setNext(before, cont);
		replaceMacro(name, start, node);
		before = findNextKeyword(node, "macro");
	}
	createFileWithData(node, strcatConst(fileName, OUTLOC));
}
