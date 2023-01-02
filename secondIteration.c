#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "secondIteration.h"
#define STARTVLUE 100
#define EMPTY "00000000"
#define ZERO "00"
#define OBLOC ".ob"

struct Node* codeHead;
int ic;
char* lastArg;
int isInstruction;

/* returns strcat after malloc */
char* strcatConst(char* src, char* des)
{
	char* res = (char*)malloc(sizeof(char) * (strlen(src)+strlen(des))+1);
	strcpy(res, src);
	return strcat(res, des);
}
/* adds code to the list */
void addCode(char* data) /* accepts bin only */
{
	codeHead = push(codeHead, binToBase32(data));
	setNumber(codeHead, ic);
	ic++;
} 
/* adds 10 zeros code to the list */
void addEmpty()
{
	addCode(strcatConst(EMPTY, ZERO));
}
/* adds code based on given arg */
char* handleArg(char* arg)
{
        char* beforeDot;
        char* temp;
        int i;
	struct Node* node;
	if (isRegister(arg) == 1)
	{
		if (regBool == 0)
		{
			regBool = 1;
			lastArg = (char*)malloc(sizeof(char) * strlen(arg));
			strcpy(lastArg, arg);
		}
		else
		{
			addCode((strcat(registerToBin(lastArg, 4), strcat(registerToBin(arg, 4), ZERO))));
			lastArg = NULL;
		}
			
	}
	else
		if (regBool == 1)
		{
			addCode((strcat(registerToBin(lastArg, 4), numToBin("0", 6))));
			lastArg = NULL;
		}		
	if (lastArg != NULL && regBool == 0)
	{
		addCode(strcatConst(strcatConst(numToBin("0", 4), registerToBin(lastArg, 4)), ZERO));
		lastArg = NULL;
	}
	if (isComplexArg(arg) == 1)
	{
		temp = args;
		args = arg;
		beforeDot = getNextAfterChar('.');
		handleArg(beforeDot);
		handleArg(args);
		args = temp;
	}
	if(isArgNumber(arg)==1)
		addCode((strcat(numToBin(arg+1, 8), ZERO)));
	if (isNumber(arg) == 1)
        {
		if (isInstruction == 0)
			addCode((strcat(numToBin(arg, 8), ZERO)));
		else
			addCode((numToBin(arg, 10)));
        }
	node = isExist(strings, arg);
	if (node != NULL)
		addCode((strcat(numToBin(getNumber(node), 8), "10")));
	node = isExist(structs, arg);
	if (node != NULL)
		addCode((strcat(numToBin(getNumber(node), 8), "10")));
	node = isExist(datas, arg);
	if (node != NULL)
		addCode((strcat(numToBin(getNumber(node), 8), "10")));
	node = isExist(symbols, arg);
	if (node != NULL)
		addCode((strcat(numToBin(getNumber(node), 8), "10")));
	node = isExist(externs, arg);
	if (node != NULL)
		addCode(strcatConst(EMPTY, "01"));
	if (isString(arg) == 1)
	{
		i = 1;
		while (arg[i] != '\"')
		{
			addCode(charToBin(arg[i]));
			i++;
		}
		addEmpty();
	}
        return "";
}
/* adds code based on given args */
void handleArgs()
{
        char* arg;
	if (args != NULL)
        {
	arg = getNextAfterChar(',');
	while (arg != NULL)
	{
		handleArg(arg);
		arg = getNextAfterChar(',');
	}
	handleArg(args);
	regBool = 0;
        }
}
/* secondIteration */
void secondIteration(struct Node* cmdNode)
{
        char* symbol;
        char* type;
        char* temp;
        char* src;
        char* trgt;
        char* trgtType;
        char* srcType;
	code = push(code, "");
	codeHead = code;
	ic = STARTVLUE;
	while (cmdNode != NULL)
	{
		atm = getData(cmdNode);
		if (atm != NULL)
		{
			isInstruction = 0;
			regBool = 0;
			symbol = getNextWord();
			type = getNextWord(); 
			args = getNextWordAsIs();
			if (strchr(symbol, ':') == NULL && strchr(symbol, '.') == NULL)
			{
				args = type;
				type = symbol;
			}
			if (strcmp(type, ".data") == 0 || strcmp(type, ".string") == 0 || strcmp(type, ".struct") == 0)
				isInstruction = 1;
			if (strcmp(symbol, ".entry") != 0 && strcmp(symbol, ".extern") != 0)
			{
				temp = args;
				src = getNextAfterChar(',');
				trgt = args;
				if (src != NULL && trgt == NULL)
				{
					trgt = src;
					src = "N";
				}
				trgtType = getArgType(trgt);
				srcType = getArgType(src);
				args = temp;
				if (isInstruction == 0)
					addCode(strcat(strcat(strcat(numToBin(getCode(search(type)), 4), numToBin(srcType, 2)), numToBin(trgtType, 2)), ZERO));
				handleArgs();
			}
		}
		cmdNode = getNext(cmdNode);
	}
	code = getNext(code);
	createFileWithIC(code, strcatConst(fileName, OBLOC),1);
}

