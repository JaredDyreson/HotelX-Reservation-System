#pragma once

#include <iostream>
#include <map>

#include "../../../include/Technical/Persistence/credentials.hpp"
#include "../../../include/Technical/Persistence/database.hpp"

namespace TechnicalServices::Persistence {
  Database::Database() {
    this->database = std::map<Domain::Actors::Person, credentials>();
  }
  void Database::insertElement(Domain::Actors::Person* person) {
      auto creds = (*person).getCredentials();
      if(this->database.find(*person) == this->database.end()) {
        auto it = this->database.begin();
        this->database.insert(it, std::pair<Domain::Actors::Person, credentials>(*person, creds));
      } else {
        std::cerr << (*person).getName() << " is already in the database" << std::endl;
      }
  }
  size_t Database::size() {
    return this->database.size();
  }
};
