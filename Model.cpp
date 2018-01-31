

#include "Model.h"
#include <string.h>

void Database::getString(const std::string &query,std::vector<std::string> &result,int index,int max_size,int *size)
{
  sqlite3_stmt   *res=NULL;
  const char     *tail=NULL;
  int rc=0;
  int i=0;
  std::cout << "getString["
    << query
    << "] index["
    << index
    <<"]"
    << std::endl;
  rc=sqlite3_prepare_v2(db,query.c_str(),-1,&res,&tail);
  if (rc != SQLITE_OK) {
    std::cerr << "getString We did not get any data![" << rc << "]" << std::endl;
  }else{
    rc=sqlite3_step(res);
    if(rc==SQLITE_DONE){
      std::cerr << "getString ["
        << rc
        << "] no entries found!"
        << std::endl;
      sqlite3_finalize(res);
      *size=0;
      return;
    }
    if (rc != SQLITE_ROW) {
      std::cerr << "getString ["
        << rc
        << "]ERROR sqlite3_step: "
        << sqlite3_errmsg(db)
        << std::endl;
      sqlite3_close(db);
      return;
    }
    i=0;
    while(rc != SQLITE_DONE) {
      std::cerr << "getString "
        << sqlite3_column_int(res, 0)
        << " "
        << (const char*)sqlite3_column_text(res, 1)
        << std::endl;
      result.push_back((char*)sqlite3_column_text(res, index));
      rc=sqlite3_step(res);
      ++i;
      if(i==max_size)
        break;
    }
  }
  *size=i;
  sqlite3_finalize(res);
}
void Database::getInt(const std::string &query,int  *result,int index,int max_size,int *size){
  sqlite3_stmt   *res=NULL;
  const char     *tail=NULL;
  int rc;
  int i=0;
  std::cout << "getInt["
    << query
    << "] index["
    << index
    << "]"
    <<std::endl;
  rc=sqlite3_prepare_v2(db,query.c_str(),-1,&res,&tail);
  if (rc != SQLITE_OK) {
    std::cerr << "getInt We did not get any data!" << std::endl;
  }else{
    rc=sqlite3_step(res);
    if(rc==SQLITE_DONE){
      std::cerr << "getInt ["
        << rc
        << "] no entries found!"
        << std::endl;
      sqlite3_finalize(res);
      *size=0;
      return;
    }
    if (rc != SQLITE_ROW) {
      std::cerr << "getInt ["
        << rc
        << "]ERROR sqlite3_step: "
        << sqlite3_errmsg(db)
        << std::endl;
      sqlite3_close(db);
      return;
    }
    i=0;
    while(rc != SQLITE_DONE) {
      *result=sqlite3_column_int(res, index);
      std::cerr << "getInt["
        << index
        << "] "
        << *result
        << std::endl;
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
void Database::getColumn(const std::string &query,int  *result,int start,int end){
  sqlite3_stmt   *res=NULL;
  const char     *tail=NULL;
  int rc;
  int i=0;
  int j;
  std::cout << "getColumn["
    << query
    << "]"
    << std::endl;
  rc=sqlite3_prepare_v2(db,query.c_str(),-1,&res,&tail);
  if (rc != SQLITE_OK) {
    std::cerr << "getColumn We did not get any data!" << std::endl;
  }else{
    rc=sqlite3_step(res);
    if(rc==SQLITE_DONE){
      std::cerr <<  "getColumn ["
        << rc
        << "] no entries found!"
        << std::endl;
      sqlite3_finalize(res);
      return;
    }
    if (rc != SQLITE_ROW) {
      std::cerr << "getColumn ["
        << rc
        << "]ERROR sqlite3_step: "
        << sqlite3_errmsg(db)
        << std::endl;
      sqlite3_close(db);
      return;
    }
    i=0;
    while(rc != SQLITE_DONE) {
      for(j=start;j<=end;j++){
        *result=sqlite3_column_int(res, j);
        std::cerr << "getColumn["
          << j
          << "] "
          << *result
          << std::endl;
        ++result;
      }
      rc=sqlite3_step(res);
      ++i;
    }
  }
  sqlite3_finalize(res);
}

void Database::getLine(const std::string &query,char*output){
  sqlite3_stmt   *res=NULL;
  const char     *tail=NULL;
  int rc;
  int i=0;
  char buffer[1024];
  char *begin=(char*)&buffer;
  char*ptr=(char*)&buffer;
  buffer[0]='\0';
  std::cout << "getLine["
    << query
    << "]"
    << std::endl;
  rc=sqlite3_prepare_v2(db,query.c_str(),-1,&res,&tail);
  if (rc != SQLITE_OK) {
    std::cerr << "getLine We did not get any data!" << std::endl;
  }else{
    rc=sqlite3_step(res);
    if(rc==SQLITE_DONE){
      std::cerr << "getLine ["
        << rc
        << "] no entries found!"
        << std::endl;
      sqlite3_finalize(res);
      return;
    }
    if (rc != SQLITE_ROW) {
      std::cerr << "getLine ["
        << rc
        << "]ERROR sqlite3_step: "
        << sqlite3_errmsg(db)
        << std::endl;
      sqlite3_close(db);
      return;
    }
    i=0;
    while(rc != SQLITE_DONE) {
      std::cerr << "getLine["
        << sqlite3_column_int(res, 0)
        << "] "
        << sqlite3_column_text(res, 1)
        << std::endl;

      strcat(ptr,(const char*)sqlite3_column_text(res, 1));
      ptr+=strlen(ptr);
      ++ptr;
      *ptr='\0';
      rc=sqlite3_step(res);
      ++i;
    }
  }
  *ptr='\0';++ptr;
  *ptr='\0';
  memcpy(output,buffer,ptr-begin);
  sqlite3_finalize(res);
}
int Database::sql(const std::string &query){
  int rc;
  std::cout << "sql[" << query << "]" << std::endl;
  rc=sqlite3_exec(db,query.c_str(),0,0,0);
  if (rc != SQLITE_OK) {
    std::cerr << "sql failed! [" << query << "]" << std::endl;
  }
}
int Database::QueryGetInt(const std::string &query){
  sqlite3_stmt   *res=NULL;
  const char     *tail=NULL;
  int rc;
  int i=0;
  int ret=0;

  std::cout << "QueryGetInt[" << query << "]" << std::endl;
  rc=sqlite3_prepare_v2(db,query.c_str(),-1,&res,&tail);
  if (rc != SQLITE_OK) {
    std::cerr<< "QueryGetInt We did not get any data!" << std::endl;
  }else{
    rc=sqlite3_step(res);
    if(rc==SQLITE_DONE){
      std::cerr << "QueryGetInt [" << rc << "] no entries found!" << std::endl;
      sqlite3_finalize(res);
      return -1;
    }
    if (rc != SQLITE_ROW) {
      std::cerr << "QueryGetInt [" << rc << "]ERROR sqlite3_step: " << sqlite3_errmsg(db) << std::endl;
      sqlite3_close(db);
      return -1;
    }
    i=0;
    while(rc != SQLITE_DONE) {
      std::cout << "QueryGetInt[" << sqlite3_column_int(res, 0) << "]" << std::endl;
      ret=sqlite3_column_int(res, 0);
      rc=sqlite3_step(res);
      ++i;
    }
  }
  sqlite3_finalize(res);
  return ret;
}
