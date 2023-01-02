#pragma once
struct DataItem* data;
struct Node* getNext(struct Node* node);
void setNext(struct Node* node, struct Node* data);
char* removeSpaces(char* data);
struct Node* isExist(struct Node* node, char data[]);
struct Node* symbols;
struct Node* entrys;
struct Node* externs;
struct Node* structs;
struct Node* datas;
struct Node* strings;
char* fileName;
int errorFound;
struct Node* push(struct Node* from, char new_data[]);
void createFileWithData(struct Node* node, char* loc);
int checkArgsByCMD(char cmd[], char argType, int field);
char* getArgs(struct Node* node);
void setArgs(struct Node* node, char arg[]);
char* numToBase32(char data[]);
char* numToBin(char num[], int bits);
void setError(char* msg);
char* strcatConst(char* src, char* des);
void printListNewLine(struct Node* node);
void setNumber(struct Node* node, int num);
char* getData(struct Node* node);
char* getNumber(struct Node* node);
char* getOp(struct DataItem* data);
char* getCode(struct DataItem* data);
char* getTarget(struct DataItem* data);
char* getSrc(struct DataItem* data);
char* removeSlashN(char* data);
