#pragma once
#include <string>
#include <vector>

#include "sqlite3.h"

class database {
 public:
  ~database();
  static database& instance();
  void init(const std::string databaseName);
  void createDatabase();
  void closeDatabase();
  void createTable(const std::string tableName,
                   const std::string createTableCommand);
  void sqlCmd(const std::string query);

  void getInt(const std::string& query,
              int* result,
              int index,
              int max_size,
              int* size);
  void getLine(const std::string& query, char* output);
  void getColumn(const std::string& query, int* result, int start, int end);
  int queryGetInt(const std::string& query);
  void getString(const std::string& query,
                 std::vector<std::string>& result,
                 int index,
                 int max_size,
                 int* size);

 private:
  std::string m_databaseName;
  sqlite3* m_db;
};

void startDatabase(const std::string databaseName);
