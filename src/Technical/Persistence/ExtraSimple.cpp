#pragma once

#include "../../../include/Technical/Persistence/ExtraSimple.hpp"

#include <fstream>    // streamsize
#include <iomanip>    // quoted()
#include <limits>     // numeric_limits
#include <memory>     // make_unique()
#include <string>
#include <vector>
#include <iostream>

#include "../../../include/Technical/Logging/SimpleLogger.hpp"
#include "../../../include/Technical/Persistence/PersistenceHandler.hpp"

// NOTE : std::cout replaces _logger for now

namespace
{
  // User defined manipulator with arguments that allows std::istream::ignore to be called "in-line" (chained)
  // Usage example:
  //    stream >> first >> ignore(',') second >> ignore('\n') ;
  struct ignore
  {
    char _seperator;
    ignore( char delimiter = '\n' ) : _seperator( delimiter ) {}
  };

  std::istream & operator>>( std::istream & s, ignore && delimiter )
  {
    s.ignore( std::numeric_limits<std::streamsize>::max(), delimiter._seperator );
    return s;
  }
}    // namespace




namespace Technical::Persistence
{
  // Design decision/Programming note:
  //  - The persistence database contains adaptation data, and one of the adaptable items is which Logger component to use
  //  - The factory function Technical::Logging::create(std::ostream &) depends of the persistence database to obtain
  //    through adaptation data which kind of Logging component to create
  //  - However, the Persistence database implementations, like this one, should (must?) be able to log messages
  //  - Therefore, to maintain the design decision to allow Logging to depend on Persistence, but not Persistence to depend on
  //    Logging, we mustn't create this logger through the LoggingHandler interface, but rather select and create a specific Logger
  
  //    TODO
  //
  ExtraSimpleDB::ExtraSimpleDB() : _loggerPtr( std::make_unique<Technical::Logging::SimpleLogger>() )
  {
    _logger << "ExtraSimple DB being used and has been successfully initialized";


    // Let's look for an adaptation data file, and if found load the contents.  Otherwise create some default values.
    std::ifstream adaptationDataFile( "AdapatableData.dat", std::ios::binary );

    if( adaptationDataFile.is_open() )
    {
      // Expected format:  key = value
      // Notes:
      //   1) if key or value contain whitespace, they must be enclosed in double quotes
      //   2) if the same Key appears more than once, last one wins
      //   3) everything after the value is ignored, allowing that space to be used as comments
      //   4) A Key of "//" is ignored, allowing the file to contain comment lines of the form // = ...
      std::string key, value;
      while( adaptationDataFile >> std::quoted( key ) >> ignore( '=' ) >> std::quoted( value ) >> ignore( '\n' ) )   _adaptablePairs[key] = value;
      _adaptablePairs.erase( "//" );
    }

    else
    {
      _adaptablePairs = { /* KEY */               /* Value*/
                          {"Component.Logger",    "ExtraSimple Logger"},
                          {"Component.UI",        "ExtraSimple UI"}
//                        {"Component.UI",        "Contracted UI"}
                        };
    }
  }




  ExtraSimpleDB::~ExtraSimpleDB() noexcept
  {
    std::cout << "ExtraSimple DB shutdown successfully";
  }




  std::vector<std::string> ExtraSimpleDB::findRoles()
  {
    return { "Clerk", "Client"};
  }




  UserCredentials ExtraSimpleDB::findCredentialsByName( const std::string & name )
  {
    static std::vector<UserCredentials> storedUsers =
    {
    // Username    Pass Phrase         Authorized roles
      {"Jared",     "coffeerulz",     {"Clerk", "Client"}},
      {"Tomas", "teacherapple",   {"Clerk"}},
    };

    for( const auto & user : storedUsers ) if( user.userName == name ) return user;

    // Name not found, log the error and throw something
    std::string message = __func__;
    message += " attempt to find user \"" + name + "\" failed";

    std::cout << message;
    throw PersistenceHandler::NoSuchUser( message );
  }




  const std::string & ExtraSimpleDB::operator[]( const std::string & key ) const
  {
    auto pair = _adaptablePairs.find( key );
    if( pair != _adaptablePairs.cend() ) return pair->second;

    // Key not found - error
    std::string message = __func__;
    message += " attempt to access adaptation data with Key = \"" + key + "\" failed, no such Key";

    std::cout << message;
    throw NoSuchProperty( message );
  }
} // namespace Technical::Persistence

