#pragma once

struct Node* symbols;
struct Node* entrys;
struct Node* externs;
struct Node* structs;
struct Node* datas;
struct Node* strings;
char* atm;
char* args;
struct DataItem* search(char cmd[]);
char* getTarget(struct DataItem* data);
char* getSrc(struct DataItem* data);
char* getNextWord();
char* getData(struct Node* node);
int isRegister(char* word);
int isNumber(char* str);
int isArgNumber(char* word);
int isString(char* str);
char* getNextAfterChar(char ch);
char* getArgs(struct Node* node);
struct Node* getNext(struct Node* node);
struct Node* isExist(struct Node* node , char data[]);
int errorFound;
