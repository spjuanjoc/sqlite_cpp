//
// Created by juan.castellanos on 25/11/20.
//
#pragma once

#include "IDataBase.h"
#include <string>
#include <vector>

class RecordFinder
{
private:
  IDataBase& db;

public:
  int totalValue(const std::vector<std::string>& values)
  {
    int result = 0;

    for (const auto& it : values)
    {
//      result += db.getValue(it);
    }

    return result;
  }
};
