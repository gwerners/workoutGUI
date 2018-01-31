
#include "sqlite3.h"

int getWeekDay();
sqlite3 * OpenDB(const char *name);
void CloseDB();
void QueryStr(sqlite3 *db,const char*query,char**result,int index,int max_size,int *size);
void QueryInt(sqlite3 *db,const char*query,int  *result,int index,int max_size,int *size);
void QueryColumn(sqlite3 *db,const char*query,int  *result,int start,int end);
void Update(sqlite3 *db,const char*query);

void QueryLine(sqlite3 *db,const char*query,char*output);
int QueryGetInt(sqlite3 *db,const char*query);
