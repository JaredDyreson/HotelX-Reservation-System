#pragma once

#include <iostream>
#include <map>

#include "dataclasses.hpp"
#include "database.hpp"
#include "credentials.hpp"

namespace TechnicalServices::Persistence::DataBase {

  class Database {
    public:
      Database(std::map<std::string, std::string>);
      std::string get(std::string);
      bool contains(std::string);
      size_t size();

    private:
      std::map<std::string, std::string> database;
    };
}
