#pragma once
struct DataItem* data;
struct Node* code;
struct Node* symbols;
struct Node* entrys;
struct Node* externs;
struct Node* structs;
struct Node* datas;
struct Node* strings;
char* atm;
char* args;
int regBool;
char* fileName;
char* charToBin(char data);
char* numToBase32(char data[]);
char* opToBin(char data[]);
char* registerToBin(char data[], int bits);
char* numToBin(char num[], int bits);
char* opToBin(char data[]);
char* getArgType(char* arg);
int isRegister(char* word);
int isNumber(char* str);
int isArgNumber(char* word);
int isString(char* str);
int isComplexArg(char* arg);
int isExtern(char* word);
char* getNextWord();
struct Node* push(struct Node* from, char new_data[]);
struct DataItem* search(char cmd[]);
int isStruct(char* word);
struct Node* isExist(struct Node* node, char data[]);
char* getNumber(struct Node* node);
void setNumber(struct Node* node, int num);
char* binToBase32(char* data);
char* charToBin(char data);
char* getCode(struct DataItem* data);
void printListNewLine(struct Node* node);
char* registerToBin(char data[], int bits);
char* getNextWordAsIs();
char* getNextAfterChar(char ch);
char* getData(struct Node* node);
struct Node* getNext(struct Node* node);
void createFileWithIC(struct Node* head, char* loc, int revert);
