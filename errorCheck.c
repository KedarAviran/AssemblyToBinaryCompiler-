#include <stdio.h>
#include <string.h>
#include "errorCheck.h"

/* sets error msg and turn on error bit*/
void setError(char* msg)
{
	errorFound = 1;
	msg = strcat(msg, "\n");
	printf("%s", msg);
}
/* check .data structs*/
void checkDatas()
{
	struct Node* cmdNode;
        char* arg;
        cmdNode = datas;
	while (cmdNode != NULL)
	{
		args = getArgs(cmdNode);
		arg = getNextAfterChar(',');
		while (arg != NULL)
		{
			if (isNumber(arg) == 0)
				setError("arg for .data is not a number");
			arg = getNextAfterChar(',');
		}
		if (isNumber(args) == 0)
			setError("arg for .data is not a number");
		cmdNode = getNext(cmdNode);
	}
}
/* check .string structs*/
void checkStrings()
{
        char* arg;
	struct Node* cmdNode;
        cmdNode = strings;
	while (cmdNode != NULL)
	{
		args = getArgs(cmdNode);
		arg = getNextAfterChar(',');
		if (arg != NULL)
			setError("ERROR More than 1 arg in .string");
		if(isString(args)==0)
			setError("ERROR arg is not a string in .string");
		cmdNode = getNext(cmdNode);
	}
}
/* check .structs*/
void checkStructs()
{
	struct Node* cmdNode;
        char* arg;
        cmdNode = structs;
	while (cmdNode != NULL)
	{
		args = getArgs(cmdNode);
		arg = getNextAfterChar(',');
		while (arg != NULL)
		{
			if (isNumber(arg) == 0 && isString(arg) == 0)
				setError("arg for .struct is not a number nor a string");
			arg = getNextAfterChar(',');
		}
		if (isNumber(args) == 0 && isString(args) == 0)
			setError("arg for .struct is not a number nor a string");
		cmdNode = getNext(cmdNode);
	}
}
/* return 1 if word is struct else 0*/
int isStruct(char* word)
{
	if (isExist(structs, word) == NULL)
		return 0;
	return 1;
}
/* return 1 if word is extern else 0*/
int isExtern(char* word)
{
	if (isExist(externs, word) == NULL)
		return 0;
	return 1;
}
/* return 1 if word is outsidesymbol else 0*/
int isOutSideSymbol(char* word)
{
	if (isExist(symbols, word) == NULL && isExist(structs, word) == NULL && isExist(datas, word) == NULL && isExist(strings, word) == NULL && isExist(externs, word) == NULL)
		return 0;
	return 1;
}
/* return 1 if word is complex arg (like s1.2) else 0*/
int isComplexArg(char* arg)
{
        char* beforeDot;
	char* temp;
        temp=args;
	args = arg;
	if (strchr(arg, '.') != NULL)
	{
		beforeDot = getNextAfterChar('.');
		if (isStruct(beforeDot) == 1 && isNumber(args) == 1)
		{
			args = temp;
			return 1;
		}
	}
	args = temp;
	return 0;

}
/* return number of the arg type*/
char* getArgType(char* arg)
{
	if (arg == NULL)
		return "N";
	if (isArgNumber(arg) == 1)
		return "0";
	if (isOutSideSymbol(arg) == 1)
		return "1";
	if (isComplexArg(arg) == 1)
		return "2";
	if (isRegister(arg) == 1)
		return "3";
        return "-1";
}
/* check for errors*/
void errorCheck(struct Node* cmdNode)
{
        char* symbol;
        char* type;
        char* src;
        char* trgt;
        struct DataItem* data;
	while (cmdNode != NULL)
	{
		atm = getData(cmdNode);
		if (atm != NULL)
		{
			symbol = getNextWord();
			type = getNextWord(); 
			args = getNextWord();
			if (strchr(symbol, ':') == NULL && strchr(symbol, '.') == NULL)
			{
				args = type;
				type = symbol;
			}
			if (strcmp(type, ".data") != 0 && strcmp(type, ".string") != 0 && strcmp(type, ".struct") != 0 && strcmp(symbol, ".entry") != 0 && strcmp(symbol, ".extern") != 0)
			{
				src = getNextAfterChar(',');
				if (getNextAfterChar(',') != NULL)
					setError("ERROR more than 2 args");
				trgt = args;
				if (src != NULL && trgt == NULL)
				{
					trgt = src;
					src = "N";
				}
				trgt = getArgType(trgt);
				src = getArgType(src);
				data = search(type);
				if (data == NULL)
					setError("ERROR unkown op");
				if (strstr(getTarget(data), trgt) == NULL || strstr(getSrc(data), src) == NULL)
					setError("this type of OP does not accept these args");
			}
		}
		cmdNode = getNext(cmdNode);
	}
	checkDatas();
	checkStrings();
	checkStructs();
}
