#pragma once

#include <string>

class IDataBase
{
public:
  virtual ~IDataBase() = default;
  virtual int getAll(const std::string& name) = 0;
};