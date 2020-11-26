#pragma once

#include <string>

class IDataBase
{
public:
  virtual int getAll(const std::string& name) = 0;
};