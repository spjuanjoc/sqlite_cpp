#include "DataBase.h"
#include "RecordFinder.h"
#include <iostream>

/**
DROP TABLE  dual;

CREATE TABLE dual (
    Dummy varchar2(255),
    Value int
 );

INSERT INTO "dual" VALUES('hello',10);
INSERT INTO "dual" VALUES('goodbye',20);

select * from dual;
*/

int main()
{
  std::cout << "Hello, SQLite!\n";

  const std::string tableName{"dual"};
  static DataBase& db = DataBase::instance();
  db.createTable(tableName);
  db.getAll(tableName);

  return 0;
}
