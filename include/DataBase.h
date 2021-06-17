#pragma once

#include "IDataBase.h"
#include <fmt/format.h>
#include <sqlite3.h>
#include <iostream>

class DataBase : public IDataBase
{

public:

  static DataBase& instance()
  {
    static DataBase database;
    return database;
  }

  ~DataBase() override
  {
    std::cout << "database closed\n";
    sqlite3_close(m_db_handler);
  }


  DataBase(DataBase const&) = delete;
  DataBase(DataBase&&)      = delete;
  DataBase& operator=(DataBase const&) = delete;
  DataBase& operator=(DataBase&&) = delete;


  int createTable(const std::string& name)
  {
    std::string drop = fmt::format( "DROP TABLE {0}", name);
    std::cout << "drop: " << drop << '\n';

    if (runQuery(drop.c_str()) != SQLITE_OK)
    {
      sqlite3_free(m_error_message);
    }

    std::string create = fmt::format(
      "CREATE TABLE {0} "
      "(Col1 varchar2(255), Col2 int);",
      name);

    std::cout << "create: " << create << '\n';

    int result = runQuery(create.c_str());

    if (result != SQLITE_OK)
    {
      std::cerr << "SQL error: " << m_error_message << '\n';
      sqlite3_free(m_error_message);
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
    std::string col1{"value10"};
    int col2 = 10;

    std::string insert = fmt::format(
      "INSERT INTO {0} "
      "VALUES('{1}',{2});",
      name,
      col1,
      col2);

    std::cout << "insert: " << insert << '\n';

    int result = runQuery(insert.c_str());

    if (result != SQLITE_OK)
    {
      std::cerr << "SQL error: " << m_error_message << '\n';
      sqlite3_free(m_error_message);
    }

    return result;
  }

  int getAll(const std::string& name) override
  {
    std::cout << "Values:\n";
    std::string query = fmt::format("SELECT * FROM {0}", name);
    std::cout << "query: " << query << '\n';

    int result = runQuery(query.c_str());

    if (result != SQLITE_OK)
    {
      std::cerr << "SQL error: " << m_error_message << '\n';
      sqlite3_free(m_error_message);
    }

    return result;
  }

protected:
  DataBase()
  {
    std::cout << "database open\n";
    m_db_result = sqlite3_open(m_db_name, &m_db_handler);
  }

  static int printCallback([[maybe_unused]]void* data, int rows, char** values, char** columnName)
  {
    for (int i = 0; i < rows; ++i)
    {
      std::cout << columnName[i] << " : " << values[i] << '\n';
    }
    return 0;
  };

  int runQuery(const char * query)
  {
    return sqlite3_exec(m_db_handler, query, printCallback, m_data, &m_error_message);
  }

private:
  int         m_db_result     = 0;
  const char* m_db_name       = "../test.db";
  sqlite3*    m_db_handler    = nullptr;
  char*       m_error_message = nullptr;
  void*       m_data          = nullptr;
};
