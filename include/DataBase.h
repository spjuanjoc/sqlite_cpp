#pragma once

#include "sqlite3.h"
#include "IDataBase.h"
#include <iostream>

class DataBase : public IDataBase
{
private:
  int         dbResult_     = 0;
  const char* dbName_       = "../test.db";
  sqlite3*    dbHandler_    = nullptr;
  char*       errorMessage_ = nullptr;
  void*       data_         = nullptr;

protected:
  DataBase()
  {
    std::cout << "database open\n";
    dbResult_ = sqlite3_open(dbName_, &dbHandler_);
  }

  static int printCallback(void* data, int rows, char** values, char** columnName)
  {
    for (int i = 0; i < rows; ++i)
    {
      std::cout << columnName[i] << " : " << values[i] << '\n';
    }
    return 0;
  };

  int runQuery(const char * query)
  {
    return sqlite3_exec(dbHandler_, query, printCallback, static_cast<void*>(data_), &errorMessage_);
  }

public:
  DataBase(DataBase const&) = delete;
  DataBase(DataBase&&)      = delete;
  DataBase& operator=(DataBase const&) = delete;
  DataBase& operator=(DataBase&&) = delete;

  ~DataBase()
  {
    std::cout << "database closed\n";
    sqlite3_close(dbHandler_);
  }

  static DataBase& instance()
  {
    static DataBase database;
    return database;
  }

  int createTable(const std::string& name)
  {
    std::string drop{"DROP TABLE "};
    drop.append(name);
    drop.append(";");

    if (runQuery(drop.c_str()) != SQLITE_OK)
    {
      sqlite3_free(errorMessage_);
    }

    std::string create{"CREATE TABLE "};
    create.append(name);
    create.append(" (Col1 varchar2(255), Col2 int);");

    int result = runQuery(create.c_str());

    if (result != SQLITE_OK)
    {
      std::cerr << "SQL error: " << errorMessage_ << '\n';
      sqlite3_free(errorMessage_);
    }
    else
    {
      std::cout << "Table " << name << " created.\n";
      insertInto(name);
    }

    return result;
  }

  int insertInto(const std::string& name)
  {
    std::string insert{"INSERT INTO "};
    insert.append(name);
    insert.append(" VALUES('first',10);");

    int result = runQuery(insert.c_str());

    if (result != SQLITE_OK)
    {
      std::cerr << "SQL error: " << errorMessage_ << '\n';
      sqlite3_free(errorMessage_);
    }

    return result;
  }

  int getAll(const std::string& name) override
  {
    std::cout << "Values:\n";
    std::string select{"SELECT * FROM "};
    select.append(name);

    int result = runQuery(select.c_str());

    if (result != SQLITE_OK)
    {
      std::cerr << "SQL error: " << errorMessage_ << '\n';
      sqlite3_free(errorMessage_);
    }

    return result;
  }
};
