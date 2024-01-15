#include "database.hpp"
#include <fmt/color.h>
#include <fmt/format.h>

void startDatabase(const std::string databaseName) {
  fmt::print(fmt::emphasis::bold | fg(fmt::color::green),
             "Starting database\n");
  database::instance().init(databaseName);
  fmt::print(fmt::emphasis::bold | fg(fmt::color::green),
             "initialization finished\n");
}
database::~database() {
  closeDatabase();
}
database& database::instance() {
  static database db;
  return db;
}

int checkCallback(void* NotUsed, int argc, char** argv, char** azColName) {
  NotUsed = 0;
  for (int i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  return 0;
}
void database::init(const std::string databaseName) {
  m_databaseName = databaseName;

  createDatabase();
#include "tableSql.cpp"
  createTable("Status", sqlStatus);
  createTable("Routine", sqlRoutine);
  createTable("Day", sqlDay);
  createTable("Movement", sqlMovement);
  createTable("Pushups", sqlPushups);
  createTable("Squats", sqlSquats);
  createTable("Pullups", sqlPullups);
  createTable("LegRaises", sqlLegRaises);
  createTable("Bridges", sqlBridges);
  createTable("HandstandPushups", sqlHandstandPushups);
  createTable("Set0", sqlSet0);
  createTable("Set1", sqlSet1);
  createTable("Set2", sqlSet2);
  createTable("Set3", sqlSet3);
  createTable("Progress", sqlProgress);
  createTable("ProgressionIndex", sqlProgressionIndex);

  const char* sql = "SELECT * FROM Routine;";
  char* errMsg;
  int ret = sqlite3_exec(m_db, sql, checkCallback, 0, &errMsg);

  if (ret != SQLITE_OK) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow),
               "select Routine returned[{}]\n", errMsg);
    sqlite3_free(errMsg);
    fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow),
               "select on Routine error!{}-{}({})[{}][{}]\n",
               sqlite3_errcode(m_db), sqlite3_extended_errcode(m_db),
               sqlite3_errmsg(m_db), sqlite3_errstr(sqlite3_errcode(m_db)),
               sqlite3_errstr(sqlite3_extended_errcode(m_db)));
    fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow), "query[{}]\n",
               sql);
  }
}

void database::createDatabase() {
  int ret = sqlite3_open(m_databaseName.c_str(), &m_db);
  if (ret != SQLITE_OK) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
               "Can't open database({}): {}\n", m_databaseName,
               sqlite3_errmsg(m_db));
    sqlite3_close(m_db);
    m_db = nullptr;
    return;
  }
  ret = sqlite3_extended_result_codes(m_db, 1);
  if (ret != SQLITE_OK) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
               "Can't enable Extended Result Codes on database: {}\n",
               sqlite3_errmsg(m_db));
    sqlite3_close(m_db);
    m_db = nullptr;
    return;
  }
  fmt::print(fmt::emphasis::bold | fg(fmt::color::green),
             "database created: {}\n", m_databaseName);
}
void database::closeDatabase() {
  sqlite3_close(m_db);
}
void database::createTable(const std::string tableName,
                           const std::string createTableCommand) {
  int ret = sqlite3_exec(m_db, createTableCommand.c_str(), 0, 0, 0);
  if (ret != SQLITE_OK) {
    if (ret == SQLITE_ERROR) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow),
                 "table exists[{}]\n", tableName);

    } else {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow),
                 "Create table failed!{}-{}({})[{}][{}]\n",
                 sqlite3_errcode(m_db), sqlite3_extended_errcode(m_db),
                 sqlite3_errmsg(m_db), sqlite3_errstr(sqlite3_errcode(m_db)),
                 sqlite3_errstr(sqlite3_extended_errcode(m_db)));
      fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow), "query[{}]\n",
                 createTableCommand);
    }
    ret = sqlite3_exec(m_db, "ROLLBACK;", 0, 0, 0);
    if (ret == SQLITE_ERROR) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow),
                 "table failed to rollback[{}]\n", tableName);
    }
    return;
  }
  fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "table created: {}\n",
             tableName);
}
void database::sqlCmd(const std::string query) {
  char* errMsg;
  fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "{}[{}]\n",
             __FUNCTION__, query);
  int ret = sqlite3_exec(m_db, query.c_str(), 0, 0, &errMsg);
  if (ret != SQLITE_OK) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow),
               "Query returned[{}]\n", errMsg);
    sqlite3_free(errMsg);
    fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow),
               "Error {}-{}({})[{}][{}]\n", sqlite3_errcode(m_db),
               sqlite3_extended_errcode(m_db), sqlite3_errmsg(m_db),
               sqlite3_errstr(sqlite3_errcode(m_db)),
               sqlite3_errstr(sqlite3_extended_errcode(m_db)));
    fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow), "query[{}]\n",
               query);
    return;
  }
  fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "query OK: {}\n",
             query);
}

void database::getInt(const std::string& query,
                      int* result,
                      int index,
                      int max_size,
                      int* size) {
  sqlite3_stmt* res = NULL;
  const char* tail = NULL;
  int rc;
  int i = 0;
  fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "{}[{}] index[{}] \n",
             __FUNCTION__, query, index);
  rc = sqlite3_prepare_v2(m_db, query.c_str(), -1, &res, &tail);
  if (rc != SQLITE_OK) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "{} not ok\n",
               __FUNCTION__);

    fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
               "{} error!{}-{}({})[{}][{}]\n", __FUNCTION__,
               sqlite3_errcode(m_db), sqlite3_extended_errcode(m_db),
               sqlite3_errmsg(m_db), sqlite3_errstr(sqlite3_errcode(m_db)),
               sqlite3_errstr(sqlite3_extended_errcode(m_db)));
    fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow), "query[{}]\n",
               query);

  } else {
    rc = sqlite3_step(res);
    if (rc == SQLITE_DONE) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
                 "{} [{}] no entries found!\n", __FUNCTION__, rc);
      sqlite3_finalize(res);
      *size = 0;
      return;
    }
    if (rc != SQLITE_ROW) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
                 "{} sqlite3_step error!{}-{}({})[{}][{}]\n", __FUNCTION__,
                 sqlite3_errcode(m_db), sqlite3_extended_errcode(m_db),
                 sqlite3_errmsg(m_db), sqlite3_errstr(sqlite3_errcode(m_db)),
                 sqlite3_errstr(sqlite3_extended_errcode(m_db)));
      fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "query[{}]\n",
                 query);
      sqlite3_finalize(res);
      return;
    }
    i = 0;
    while (rc != SQLITE_DONE) {
      *result = sqlite3_column_int(res, index);
      fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "{} [{}] {}\n",
                 __FUNCTION__, index, *result);
      rc = sqlite3_step(res);
      ++i;
      ++result;
      if (i == max_size)
        break;
    }
  }
  *size = i;
  sqlite3_finalize(res);
}
void database::getLine(const std::string& query, char* output) {
  sqlite3_stmt* res = NULL;
  const char* tail = NULL;
  int rc;
  int i = 0;
  char buffer[1024];
  char* begin = (char*)&buffer;
  char* ptr = (char*)&buffer;
  buffer[0] = '\0';
  fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "{}[{}]\n",
             __FUNCTION__, query);
  rc = sqlite3_prepare_v2(m_db, query.c_str(), -1, &res, &tail);
  if (rc != SQLITE_OK) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
               "{} We did not get any data!\n", __FUNCTION__);
  } else {
    rc = sqlite3_step(res);
    if (rc == SQLITE_DONE) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
                 "{} [{}] no entries found!\n", __FUNCTION__, rc);
      sqlite3_finalize(res);
      return;
    }
    if (rc != SQLITE_ROW) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
                 "{} [{}] ERROR sqlite3_step: {}", __FUNCTION__, rc,
                 sqlite3_errmsg(m_db));
      sqlite3_close(m_db);
      return;
    }
    i = 0;
    while (rc != SQLITE_DONE) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::green),
                 "getLine[{}] {}\n", sqlite3_column_int(res, 0),
                 sqlite3_column_text(res, 1));

      strcat(ptr, (const char*)sqlite3_column_text(res, 1));
      ptr += strlen(ptr);
      ++ptr;
      *ptr = '\0';
      rc = sqlite3_step(res);
      ++i;
    }
  }
  *ptr = '\0';
  ++ptr;
  *ptr = '\0';
  memcpy(output, buffer, ptr - begin);
  sqlite3_finalize(res);
}
void database::getColumn(const std::string& query,
                         int* result,
                         int start,
                         int end) {
  sqlite3_stmt* res = NULL;
  const char* tail = NULL;
  int rc;
  int i = 0;
  int j;
  fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "{}[{}]\n",
             __FUNCTION__, query);
  rc = sqlite3_prepare_v2(m_db, query.c_str(), -1, &res, &tail);
  if (rc != SQLITE_OK) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
               "getColumn We did not get any data!\n");
  } else {
    rc = sqlite3_step(res);
    if (rc == SQLITE_DONE) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
                 "{} [{}] no entries found!\n", __FUNCTION__, rc);
      sqlite3_finalize(res);
      return;
    }
    if (rc != SQLITE_ROW) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
                 "{} [{}] ERROR sqlite3_step: {}", __FUNCTION__, rc,
                 sqlite3_errmsg(m_db));
      sqlite3_close(m_db);
      return;
    }
    i = 0;
    while (rc != SQLITE_DONE) {
      for (j = start; j <= end; j++) {
        *result = sqlite3_column_int(res, j);
        fmt::print(fmt::emphasis::bold | fg(fmt::color::green),
                   "getColumn[{}] {}\n", j, *result);
        ++result;
      }
      rc = sqlite3_step(res);
      ++i;
    }
  }
  sqlite3_finalize(res);
}
int database::queryGetInt(const std::string& query) {
  sqlite3_stmt* res = NULL;
  const char* tail = NULL;
  int rc;
  int i = 0;
  int ret = 0;

  fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "{}[{}]\n",
             __FUNCTION__, query);
  rc = sqlite3_prepare_v2(m_db, query.c_str(), -1, &res, &tail);
  if (rc != SQLITE_OK) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
               "{} We did not get any data!\n", __FUNCTION__);
  } else {
    rc = sqlite3_step(res);
    if (rc == SQLITE_DONE) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
                 "{} [{}] no entries found!\n", __FUNCTION__, rc);
      sqlite3_finalize(res);
      return -1;
    }
    if (rc != SQLITE_ROW) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
                 "{} [{}] ERROR sqlite3_step: {}", __FUNCTION__, rc,
                 sqlite3_errmsg(m_db));
      sqlite3_close(m_db);
      return -1;
    }
    i = 0;
    while (rc != SQLITE_DONE) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "{}[{}] {}\n",
                 __FUNCTION__, i, sqlite3_column_int(res, 0));
      ret = sqlite3_column_int(res, 0);
      rc = sqlite3_step(res);
      ++i;
    }
  }
  sqlite3_finalize(res);
  return ret;
}
void database::getString(const std::string& query,
                         std::vector<std::string>& result,
                         int index,
                         int max_size,
                         int* size) {
  sqlite3_stmt* res = NULL;
  const char* tail = NULL;
  int rc = 0;
  int i = 0;
  fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "{}[{}] index[{}] \n",
             __FUNCTION__, query, index);
  rc = sqlite3_prepare_v2(m_db, query.c_str(), -1, &res, &tail);
  if (rc != SQLITE_OK) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
               "{} We did not get any data![{}]\n", __FUNCTION__, rc);

  } else {
    rc = sqlite3_step(res);
    if (rc == SQLITE_DONE) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
                 "{} [{}] no entries found!\n", __FUNCTION__, rc);
      sqlite3_finalize(res);
      *size = 0;
      return;
    }
    if (rc != SQLITE_ROW) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
                 "{} [{}] ERROR sqlite3_step: {}", __FUNCTION__, rc,
                 sqlite3_errmsg(m_db));
      sqlite3_close(m_db);
      return;
    }
    i = 0;
    while (rc != SQLITE_DONE) {
      fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "{} {} {}\n",
                 __FUNCTION__, sqlite3_column_int(res, 0),
                 (const char*)sqlite3_column_text(res, 1));
      result.push_back((char*)sqlite3_column_text(res, index));
      rc = sqlite3_step(res);
      ++i;
      if (i == max_size)
        break;
    }
  }
  *size = i;
  sqlite3_finalize(res);
}
