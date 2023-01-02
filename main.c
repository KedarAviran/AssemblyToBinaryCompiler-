
#include <stdio.h>
#include <string.h>
#include "main.h"
#define END ".as"

struct Node* cmd;
struct Node* code;
struct Node* symbols;
struct Node* entrys;
struct Node* externs;
struct Node* structs;
struct Node* datas;
struct Node* strings;
int errorFound;
char* fileName;

int main(int argc, char** argv)
{
        int i;
	loadData();
	for (i = 1; i < argc; i++)
	{
		errorFound = 0;
		fileName = argv[i];
		cmd = loadCodeFromFile(strcatConst(fileName, END));
		handleMacro(cmd);
		firstIteration(cmd);
		errorCheck(cmd);
		secondIteration(cmd);
	}
	return 0;
}
