#pragma once
struct Node* node;
char* numToBin(char num[], int bits);
char* registerToBin(char data[], int bits);
char* opToBin(char data[]);
char* numToBase32(char data[]);
char* charToBin(char data);
struct DataItem* search(char cmd[]);
char* getOp(struct DataItem* data);
char* getCode(struct DataItem* data);
char* getTarget(struct DataItem* data);
char* getSrc(struct DataItem* data);
char* getData(struct Node* node);
struct Node* getNext(struct Node* node);
void setNext(struct Node* node, struct Node* data);
struct Node* copy(struct Node* copy);
void conjoin(struct Node* to, struct Node* from);
char* strcatConst(char* src, char* des);
char* fileName;
