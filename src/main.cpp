#include "sqlite3.h"
#include <iostream>

static int callback(void* data, int argc, char** argv, char** azColName)
{
  std::cout << static_cast<const char*>(data) << '\n';
//  fprintf(stderr, "%s: ", (const char*) data);

  for (int i = 0; i < argc; i++)
  {

    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }

//  printf("\n");
  std::cout << std::endl;

  return 0;
}

int main()
{
  std::cout << "Hello, SQLite!\n";

  sqlite3* db;
  int      rc = sqlite3_open("../test.db", &db);

  if (rc == SQLITE_OK)
  {
    std::cout << "Database open successfully \n";

    auto query = R"(SELECT * FROM dual;)";
    char* zErrMsg = nullptr;
    const char* data = "Callback function called";
    rc = sqlite3_exec(db, query, callback, (void*)data, &zErrMsg);

    if (rc != SQLITE_OK)
    {
      std::cerr << "SQL error: " << zErrMsg << '\n';
      sqlite3_free(zErrMsg);
    }
    else
    {
      std::cout << "Done\n";
    }

    sqlite3_close(db);
  }
  else
  {
    std::cout << "Can't open database: " << sqlite3_errmsg(db) << "\n";
  }

  return 0;
}
