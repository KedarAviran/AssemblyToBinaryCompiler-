#pragma once

struct DataItem* opArray[17];
struct DataItem* search(char cmd[]);
char* getOp(struct DataItem* data);
char* getCode(struct DataItem* data);
char* getTarget(struct DataItem* data);
char* getSrc(struct DataItem* data);
char* removeSpaces(char* data);
