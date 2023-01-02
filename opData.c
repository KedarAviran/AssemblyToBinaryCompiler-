
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define opSize 16
#define CMDSIZE 32
#define FILESRC "opData.txt"
#define DATALIMIT 32  

struct DataItem 
{
    char op[CMDSIZE];
    char opCode[CMDSIZE];
    char target[CMDSIZE];
    char src[CMDSIZE];
};

struct DataItem* opArray[opSize];
/* get and sets */
char* getOp(struct DataItem* data)
{
    return data->op;
}
char* getCode(struct DataItem* data)
{
    return data->opCode;
}
char* getTarget(struct DataItem* data)
{
    return data->target;
}
char* getSrc(struct DataItem* data)
{
    return data->src;
}
/* returns cmd if it exsists else null */
struct DataItem* search(char cmd[])
{
    int i;
    for (i = 0; i < opSize; i++)
    {
        if (strcmp(opArray[i]->op, cmd) == 0)
            return opArray[i];
    }
    return NULL;
}
/* insets data to arrays */
void insert(char _opCode[], char _op[], char _src[], char _target[])
{
    int id;
    struct DataItem* item = (struct DataItem*)malloc(sizeof(struct DataItem));
    strcpy(item->op, _op);
    strcpy(item->opCode, _opCode);
    strcpy(item->target, _target);
    strcpy(item->src, _src);
    id = atoi(_opCode);
    opArray[id] = item;
}
/* prints data for debugging only */
void printOpData()
{
    int i;
    for (i = 0; i < opSize; i++)
    {
        printf("%s ",opArray[i]->opCode); 
        printf("%s ",opArray[i]->op);
        printf("%s ",opArray[i]->src);
        printf("%s ",opArray[i]->target);
    }
}
/* returns 1 if cmd accepts argtype else return 0 */
int checkArgsByCMD(char cmd[], char argType , int field) /* 0 src 1 target*/
{
    struct DataItem* item = search(cmd);
    if (item == NULL)
        return -1;
    if (field == 0 && strchr(item->src, argType) != NULL)
        return 1;
    if (field == 1 && strchr(item->target, argType) != NULL)
        return 1;
    return 0;
}
/* loads data from file at "opData" with contains all the cmds and accptable args */
void loadData()
{
    int i;
    char* code;
    char* op;
    char* src;
    char* target;
    FILE* fp;
    char buff[DATALIMIT];
    fp = fopen(FILESRC, "r");
    for (i = 0; i < opSize; i++)
    {
        fgets(buff, DATALIMIT, (FILE*)fp);
        code = strtok(buff, " ");
        op = strtok(NULL, " ");
        src = strtok(NULL, " ");
        target = strtok(NULL, " ");
        insert(code, op, src, target);
    }
    fclose(fp);
}
