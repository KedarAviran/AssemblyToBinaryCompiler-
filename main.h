#pragma once

struct Node* loadCodeFromFile(char src[]);
void handleMacro(struct Node* node);
void firstIteration(struct Node* cmdNode);
void errorCheck(struct Node* cmdNode);
void loadData();
void secondIteration(struct Node* cmdNode);
char* strcatConst(char* src, char* des);