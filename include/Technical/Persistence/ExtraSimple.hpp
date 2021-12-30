#pragma once

#include <memory>    // unique_ptr
#include <string>
#include <vector>

//#include "Technical/Logging/LoggerHandler.hpp" FIXME
//
#include "../Logging/LoggerHandler.hpp"
#include "PersistenceHandler.hpp"

namespace Technical::Persistence
{
  class ExtraSimpleDB : public Technical::Persistence::PersistenceHandler
  {
    public:
      using PersistenceHandler::PersistenceHandler;    // inherit constructors
      ExtraSimpleDB();


      // Operations
      std::vector<std::string> findRoles()                                       override;  // Returns list of all legal roles
      UserCredentials          findCredentialsByName( const std::string & name ) override;  // Returns credentials for specified user, throws NoSuchUser if user not found

      // Adaptation Data read only access.  Adaptation data is a Key/Value pair
      const std::string & operator[]( const std::string & key ) const override;


      ~ExtraSimpleDB() noexcept override;

    private:
      std::unique_ptr<Technical::Logging::LoggerHandler> _loggerPtr;

      // convenience reference object enabling standard insertion syntax
      // This line must be physically after the definition of _loggerPtr
      Technical::Logging::LoggerHandler & _logger = *_loggerPtr;


      // Super simple vector container to hold all the credentials
      // Hey, budgets constraints
      //using AdaptationData = std::vector<std::string [> values <]>;
      using AdaptationData = std::map<std::string /* keys */, std::string /* values */>;
      AdaptationData _adaptablePairs;
      std::map<std::string, std::string> database;

  }; // class ExtraSimpleDB
}  // namespace Technical::Persistence

