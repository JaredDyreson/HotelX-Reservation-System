#pragma once

#include <iostream>
#include <map>

#include "../../../include/Technical/Persistence/credentials.hpp"
#include "../../../include/Technical/Persistence/database.hpp"

namespace TechnicalServices::Persistence {
  Database::Database() {
    this->database = std::map<credentials, Domain::Actors::Person>();
  }
  void Database::insertElement(Domain::Actors::Person* person) {

      auto creds = (*person).getCredentials();
      if(this->database.find(creds) == this->database.end()) {
        auto it = this->database.begin();
        this->database.insert (it, std::pair<credentials, Domain::Actors::Person>(creds, *person));
      } else {
        std::cerr << "Person is already in the database" << std::endl;
      }
  }
  size_t Database::size() {
    return this->database.size();
  }
};
