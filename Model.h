

#ifndef __MODEL_H__
#define __MODEL_H__
#include <iostream>
#include <string>
#include <vector>

extern "C"{
#include "sqlite3.h"
}

class Database{
protected:
  sqlite3 *db;
public:
  Database(std::string db_name):db(0){
    int rc=0;
    rc = sqlite3_open(db_name.c_str(),&db);
    if( rc ){
      std::cout << "unable to open database" << std::endl;
      sqlite3_close(db);
      db=0;
    }
    //std::cout << "database " << db_name << std::endl;
    //std::cout << "handle " << db << std::endl;
  }
  ~Database(){
    if(db){
      sqlite3_close(db);
      db=0;
    }
  }
  void getString(const std::string &query,std::vector<std::string> &result,int index,int max_size,int *size);
  void getInt(const std::string &query,int  *result,int index,int max_size,int *size);
  void getColumn(const std::string &query,int  *result,int start,int end);

  void getLine(const std::string &query,char*output);
  int sql(const std::string &query);
  int QueryGetInt(const std::string &query);
};
#endif
