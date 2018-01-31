
#include "query.h"
#include <stdio.h>
#include <string.h>
#include <time.h>


int getWeekDay(){
  struct tm *ts;
  time_t timestamp = time(NULL);
  ts   = localtime(&timestamp);
  return ts->tm_wday;
}
static sqlite3 *db=NULL;
sqlite3 * OpenDB(const char *name){
  int rc=0;
  if(!db){
    rc = sqlite3_open("convict.db",&db);
    if( rc ){
      printf("unable to open database\n");
      sqlite3_close(db);
      db=NULL;
    }
  }
  return db;
}
void CloseDB(){
  if(db)
    sqlite3_close(db);
  db=NULL;
}
void QueryStr(sqlite3 *db,const char*query,char**result,int index,int max_size,int *size){
  sqlite3_stmt   *res=NULL;
  const char     *tail=NULL;
  int rc=0;
  int i=0;
  printf("QueryStr[%s] index[%d]\n",(char*)query,index);
  rc=sqlite3_prepare_v2(db,query,-1,&res,&tail);
  if (rc != SQLITE_OK) {
    printf("QueryStr We did not get any data!");
  }else{
    rc=sqlite3_step(res);
    if(rc==SQLITE_DONE){
      printf("QueryStr [%d] no entries found!\n",rc);
      sqlite3_finalize(res);
      *size=0;
      return;
    }
    if (rc != SQLITE_ROW) {
      printf("QueryStr [%d]ERROR sqlite3_step: %s\n",rc, sqlite3_errmsg(db));
      sqlite3_close(db);
      return;
    }
    i=0;
    while(rc != SQLITE_DONE) {
      printf("QueryStr %d %s\n",sqlite3_column_int(res, 0),(const char*)sqlite3_column_text(res, 1));
      *result=strdup((const char*)sqlite3_column_text(res, index));
      rc=sqlite3_step(res);
      ++i;
      ++result;
      if(i==max_size)
        break;
    }
  }
  *size=i;
  sqlite3_finalize(res);
}
void QueryInt(sqlite3 *db,const char*query,int*result,int index,int max_size,int *size){
  sqlite3_stmt   *res=NULL;
  const char     *tail=NULL;
  int rc;
  int i=0;
  printf("QueryInt[%s] index[%d]\n",(char*)query,index);
  rc=sqlite3_prepare_v2(db,query,-1,&res,&tail);
  if (rc != SQLITE_OK) {
    printf("QueryInt We did not get any data!");
  }else{
    rc=sqlite3_step(res);
    if(rc==SQLITE_DONE){
      printf("QueryInt [%d] no entries found!\n",rc);
      sqlite3_finalize(res);
      *size=0;
      return;
    }
    if (rc != SQLITE_ROW) {
      printf("QueryInt [%d]ERROR sqlite3_step: %s\n",rc, sqlite3_errmsg(db));
      sqlite3_close(db);
      return;
    }
    i=0;
    while(rc != SQLITE_DONE) {
      //printf("QueryInt[%d] %d %d %d\n",sqlite3_column_int(res, 0),sqlite3_column_int(res, 1),sqlite3_column_int(res, 2));
      *result=sqlite3_column_int(res, index);
      printf("QueryInt[%d] %d\n",index,*result);
      rc=sqlite3_step(res);
      ++i;
      ++result;
      if(i==max_size)
        break;
    }
  }
  *size=i;
  sqlite3_finalize(res);
}
void QueryColumn(sqlite3 *db,const char*query,int  *result,int start,int end){
  sqlite3_stmt   *res=NULL;
  const char     *tail=NULL;
  int rc;
  int i=0;
  int j;
  printf("QueryColumn[%s]\n",(char*)query);
  rc=sqlite3_prepare_v2(db,query,-1,&res,&tail);
  if (rc != SQLITE_OK) {
    printf("QueryColumn We did not get any data!");
  }else{
    rc=sqlite3_step(res);
    if(rc==SQLITE_DONE){
      printf("QueryColumn [%d] no entries found!\n",rc);
      sqlite3_finalize(res);
      return;
    }
    if (rc != SQLITE_ROW) {
      printf("QueryColumn [%d]ERROR sqlite3_step: %s\n",rc, sqlite3_errmsg(db));
      sqlite3_close(db);
      return;
    }
    i=0;
    while(rc != SQLITE_DONE) {
      //printf("QueryInt[%d] %d %d %d\n",sqlite3_column_int(res, 0),sqlite3_column_int(res, 1),sqlite3_column_int(res, 2));
      for(j=start;j<=end;j++){
        *result=sqlite3_column_int(res, j);
        printf("QueryColumn[%d] %d\n",j,*result);
        ++result;
      }
      rc=sqlite3_step(res);
      ++i;

    }
  }
  sqlite3_finalize(res);
}
void Update(sqlite3 *db,const char*query){
  int rc;
  rc=sqlite3_exec(db,query,0,0,0);
  if (rc != SQLITE_OK) {
    printf("Update failed!");
  }
}
void QueryLine(sqlite3 *db,const char*query,char*output){
  sqlite3_stmt   *res=NULL;
  const char     *tail=NULL;
  int rc;
  int i=0;
  char buffer[1024];
  char *begin=(char*)&buffer;
  char*ptr=(char*)&buffer;
  buffer[0]='\0';
  printf("QueryLine[%s]\n",(char*)query);
  rc=sqlite3_prepare_v2(db,query,-1,&res,&tail);
  if (rc != SQLITE_OK) {
    printf("QueryLine We did not get any data!");
  }else{
    rc=sqlite3_step(res);
    if(rc==SQLITE_DONE){
      printf("QueryLine [%d] no entries found!\n",rc);
      sqlite3_finalize(res);
      return;
    }
    if (rc != SQLITE_ROW) {
      printf("QueryLine [%d]ERROR sqlite3_step: %s\n",rc, sqlite3_errmsg(db));
      sqlite3_close(db);
      return;
    }
    i=0;
    while(rc != SQLITE_DONE) {
      printf("QueryLine[%d] %s\n",
        sqlite3_column_int(res, 0),
        sqlite3_column_text(res, 1)
      );
      strcat(ptr,sqlite3_column_text(res, 1));
      ptr+=strlen(ptr);
      ++ptr;
      *ptr='\0';
      //sqlite3_column_int(res, index);

      rc=sqlite3_step(res);
      ++i;
    }
  }
  *ptr='\0';++ptr;
  *ptr='\0';
  memcpy(output,buffer,ptr-begin);
  sqlite3_finalize(res);
}
int QueryGetInt(sqlite3 *db,const char*query){
  sqlite3_stmt   *res=NULL;
  const char     *tail=NULL;
  int rc;
  int i=0;
  int ret=0;

  printf("QueryGetInt[%s]\n",(char*)query);
  rc=sqlite3_prepare_v2(db,query,-1,&res,&tail);
  if (rc != SQLITE_OK) {
    printf("QueryGetInt We did not get any data!");
  }else{
    rc=sqlite3_step(res);
    if(rc==SQLITE_DONE){
      printf("QueryGetInt [%d] no entries found!\n",rc);
      sqlite3_finalize(res);
      return -1;
    }
    if (rc != SQLITE_ROW) {
      printf("QueryGetInt [%d]ERROR sqlite3_step: %s\n",rc, sqlite3_errmsg(db));
      sqlite3_close(db);
      return -1;
    }
    i=0;
    while(rc != SQLITE_DONE) {
      printf("QueryGetInt[%d]\n",
        sqlite3_column_int(res, 0)
      );
      ret=sqlite3_column_int(res, 0);
      rc=sqlite3_step(res);
      ++i;
    }
  }
  sqlite3_finalize(res);
  return ret;
}
