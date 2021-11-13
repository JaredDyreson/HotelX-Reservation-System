#pragma once

#include <iostream>
#include <map>

#include "dataclasses.hpp"
#include "database.hpp"
#include "credentials.hpp"

namespace TechnicalServices::Persistence::DataBase {

  class Database {
    public:
      Database();

      size_t size();

    private:
        //std::map<credentials, Domain::Actors::Person> database;
        //std::map<TechnicalServices::Persistence::DataClasses, credentials> database;

  };
}
