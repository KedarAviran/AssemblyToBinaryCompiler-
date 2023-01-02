#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "firstIteration.h"

#define STARTVLUE 100
#define MAX 82
#define ENTLOC ".ent"
#define EXTLOC ".ext"

char* atm;
char* args;
int test;
int numBool;
int regBool;
struct Node* externsHead;
struct Node* externsExport;
struct Node* entrysHead;
struct Node* symbolsHead;
struct Node* structsHead;
struct Node* datasHead;
struct Node* stringsHead;

/* deletes char from string */
char* removeAddedChar(char *str, char garbage)
{
    char *src, *dst;
    if(str==NULL)
       return NULL;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
    return str;
}
/* discards the rest of the word from atm and returns a copy of the word */
char* discardEnding()
{
        int i;
        char* copyData;
	if (atm == NULL)
		return NULL;
        if (*(atm)=='\0')
                return NULL;
	if(*(atm) == '\n')
		return NULL;
        copyData = (char*)malloc(MAX);
	strcpy(copyData, atm);
	i = 0;
	while (atm[i] != '\0')
	{
		if (*(atm + i) == ' ' || *(atm + i) == '\t' || *(atm + i) == '\n'|| *(atm + i) == '\b'|| *(atm + i) == '\a'|| *(atm + i) == '\0' || (int)(*(atm + i)) == 13)
		{
			atm = (atm + i);
			*(copyData + i) = '\0';
			return copyData;
		}
		i++;
	}
	return NULL;
}
/* returns copy of the rest of the atm as it is */
char* asIs()
{
        char* copyData;
	if (atm == NULL)
		return NULL;
	if (*(atm) == '\n')
		return NULL;
	copyData = (char*)malloc(MAX);
	strcpy(copyData, atm);
	if(*(copyData + strlen(atm)-1) == '\n')
        copyData=removeSlashN(copyData);
	return copyData;
}
/* returns the next word from atm + updates atm */
char* getNextWord()
{
	atm = removeSpaces(atm);
	return discardEnding();
}
/* returns the next word as it is from atm + updates atm */
char* getNextWordAsIs()
{
	atm = removeSpaces(atm);
	return asIs();
}
/* returns the copy of next word from args before char*/
char* getNextAfterChar(char ch)
{
        char* copyData;
        int i;
	if (args == NULL)
		return NULL;
	copyData = (char*)malloc(MAX);
	strcpy(copyData, args);
	i = 0;
	while (*(args + i) != '\0')
	{
		if (*(args + i) == ch)
		{
			args = args + i + 1;
			args = removeSpaces(args);
			*(copyData + i) = '\0';
			return copyData;
		}
		i++;
	}
	return NULL;
}
/* returns 1 if word is a symbol else 0 */
int isAnySymbol(char* word)
{
	if (isExist(symbolsHead, word) == NULL && isExist(structsHead, word) == NULL && isExist(datasHead, word) == NULL && isExist(stringsHead, word) == NULL)
		return 0;
	return 1;
}
/* returns 1 if word is a entry else 0 */
struct Node* isEntry(char* word)
{
	return isExist(entrysHead, word);
}
/* returns 1 if word is a external else 0 */
int isExtr(char* word)
{
	if (isExist(externsHead, word) != NULL)
		return 1;
	return 0;
}
/* returns 1 if word is a register else 0 */
int isRegister(char* word)
{
	if (*(word) == 'r' && atoi(word + 1) < 10 && atoi(word + 1) > -1)
		return 1;
        return 0;
}
/* returns 1 if word is a number else 0 */
int isNumber(char* str)
{
	int i;
	int minus; 
        minus = 0;
	i = 0;
	while (*(str+i) !='\0')
	{
		if (*(str+i) < '0' || *(str+i) > '9')
                {
			if (*(str+i) == '-' && minus == 0)
				minus = 1;
			else
				return 0;
                }
		i++;
	}
	return 1;
	
}
/* returns 1 if word is a #number else 0 */
int isArgNumber(char* word)
{
	if (*(word) == '#')
		return isNumber(word + 1);
        return 0;
}
/* returns 1 if word is a string else 0 */
int isString(char* str)
{
	if ((*(str + strlen(str) - 1) == '"' && *(str) == '"') || (*(str + strlen(str) - 1) == '\"' && *(str) == '\"'))
		return 1;
	return 0;
}
/* returns ic skip by arg */
int calculateICByArg(char* arg , int ic)
{
	if (isExtr(arg) == 1 && strcmp(arg,"")!=0)
	{
		struct Node* node = push(externsExport, arg);
		setNumber(node, ic);
	}
	if (isString(arg) == 1)
		return strlen(arg) - 1;
	if (isRegister(arg) == 1)
	{
		regBool = 1;
		return 0;
	}
	if (isArgNumber(arg) == 1)
	{
		numBool = 1;
		return 0;
	}
	if (strchr(arg, '.') != NULL)
		return 2;
	return 1;
}
/* updates IC */
int calculateIC(int ic)
{
	int sum;
        char* arg;
        char* temp;
	sum = 0;
	regBool = 0;
	numBool = 0;
	if (args == NULL)
		return 0;
	arg = getNextAfterChar(',');		
	while (arg != NULL)
	{
		sum = sum + calculateICByArg(arg, sum + ic+1);
		arg = getNextAfterChar(',');
	}
        
        temp=atm;
        atm=args;
        args = getNextWordAsIs();
        atm=temp;
	sum = sum + calculateICByArg(args, sum + ic + 1);
	return sum+regBool+numBool;
}
/* put dummys as first item on linkedlists */
void pushDummyAndSetHeads()
{
	externsExport = push(externsExport, "");
	externs = push(externs, "");
	entrys = push(entrys, "");
	symbols = push(symbols, "");
	structs = push(structs, "");
	datas = push(datas, "");
	strings = push(strings, "");
	externsHead = externs;
	symbolsHead = symbols;
	structsHead = structs;
	datasHead = datas;
	stringsHead = strings;
	entrysHead = entrys;
}
/* del dummys*/
void delDummy()
{
	externsExport = getNext(externsExport);
	entrys = getNext(entrysHead);
	externs = getNext(externsHead);
	symbols = getNext(symbolsHead);
	structs = getNext(structsHead);
	datas = getNext(datasHead);
	strings = getNext(stringsHead);
}
/* create file as outout as head as data on loction. if revert IC comes first*/
void createFileWithIC(struct Node* head, char* loc , int revert)
{
	if (errorFound == 0 && head != NULL)
	{
		FILE* fptr;
		fptr = fopen(loc, "w");
		while (head != NULL)
		{
			char* str;
			if (revert == 0)
				str = strcat(strcat(getData(head), "\t"), strcat(numToBase32(getNumber(head)), "\n"));
			else
				str = strcat(strcat(numToBase32(getNumber(head)), "\t"), strcat(getData(head), "\n"));
			fprintf(fptr, "%s", str);
			head = getNext(head);
		}
		fclose(fptr);
	}
}
/* firstiteration of the algorithem*/
void firstIteration(struct Node* cmdNode)
{
        int ic;
        char* symbol;
        char* type;
        int isDot;
	pushDummyAndSetHeads();
	ic = STARTVLUE;
	while (cmdNode != NULL)
	{
		atm = getData(cmdNode);
                atm=removeAddedChar(atm,13);
		if (atm != NULL)
		{
			symbol = getNextWord();
			type = getNextWord();
			args = getNextWordAsIs();
			isDot = 0;
			if (strcmp(symbol, ".entry") == 0)
			{
				entrys = push(entrys, type);
				if (args != NULL)
					setError("ERROR too many arguments");
				isDot = 1;
			}
			if (strcmp(symbol, ".extern") == 0) 
			{
				externs = push(externs, type);
				if (args != NULL)
					setError("ERROR too many arguments");
				isDot = 1;
			}
			if (strchr(symbol, ':') != NULL)
			{
				*(symbol + strlen(symbol) - 1) = '\0';
				if (isAnySymbol(symbol) == 0) 
				{
					struct Node* entr = isEntry(symbol);
					if (entr != NULL)
                                            {
						setNumber(entr, ic);
                                            }
					if (strcmp(type, ".struct") == 0)
					{
						struct Node* node = push(structs, symbol);
						setArgs(node, args);
						setNumber(node, ic);
						ic--;
					}
					else
						if (strcmp(type, ".data") == 0)
						{
							datas = push(datas, symbol);
							setArgs(datas, args);
							setNumber(datas, ic);
							ic--;
						}
						else
							if (strcmp(type, ".string") == 0)
							{
								strings = push(strings, symbol);
								setArgs(strings, args);
								setNumber(strings, ic);
								ic--;
							}
							else
							{
								symbols = push(symbols, symbol);
								setNumber(symbols, ic);
							}
                                        
					ic = ic + calculateIC(ic) + 1;
				}
				else
					setError("ERROR symbol already exist");
			}
			else
			{
				if (isDot == 0)
				{
					args = type;
					ic = ic + calculateIC(ic) + 1;
				}
			}
		}
		cmdNode = getNext(cmdNode);
	}
	delDummy();
	createFileWithIC(entrys,strcatConst(fileName,ENTLOC),0);
	createFileWithIC(externsExport, strcatConst(fileName, EXTLOC),0);
}

