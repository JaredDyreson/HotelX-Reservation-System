#pragma once

#include <iostream>
#include <map>

#include "../../../include/Domain/Actors/Person.hpp"
#include "../../../include/Technical/Persistence/credentials.hpp"

namespace TechnicalServices::Persistence {

  class Database {
    public:
      Database();
      void insertElement(Domain::Actors::Person*);
      size_t size();

    private:
        //std::map<credentials, Domain::Actors::Person> database;
        std::map<Domain::Actors::Person, credentials> database;
  };
}
