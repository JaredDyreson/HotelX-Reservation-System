#pragma once

#include <iostream>
#include <map>
#include <algorithm>

#include "../../../include/Technical/Persistence/credentials.hpp"
#include "../../../include/Technical/Persistence/database.hpp"

namespace TechnicalServices::Persistence::DataBase {
    
  Database::Database(std::map<std::string, std::string> _map) {
    this->database = _map;
  }
  std::string Database::get(std::string key) {
    return this->database[key];
  }

  bool Database::contains(std::string key) {
    return std::find(this->database.begin(), this->database.end(), this->database) != this->database.end();
  }

  size_t Database::size() {
    return this->database.size();
  }
};
