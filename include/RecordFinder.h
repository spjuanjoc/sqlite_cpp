//
// Created by juan.castellanos on 25/11/20.
//
#pragma once

#include "IDataBase.h"
#include <string>
#include <vector>

class RecordFinder
{
public:
  int totalValue(const std::vector<std::string>& values)
  {
    int result = 0;

    for (const auto& it : values)
    {
      std::cout << it << '\n';
//      result += m_db.getValue(it);
    }

    return result;
  }

private:
  static IDataBase& m_db;

};
