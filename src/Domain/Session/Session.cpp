#pragma once

#include "../../../include/Domain/Session/Session.hpp" // ignore std::any error
#include "../../../include/Technical/Persistence/credentials.hpp"

#include <any>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <stdexcept>



namespace  // anonymous (private) working area
{
  // 1)  First define all system events (commands, actions, requests, etc.)
  #define STUB(functionName)  std::any functionName( Domain::Session::SessionBase & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now

  STUB( bugPeople    ) // these are blank fuctions
  STUB( collectFines )
  STUB( help         )
  STUB( openArchives )
  STUB( payFines     )
  STUB( resetAccount )
  STUB( returnBook   )
  STUB( shutdown     )


}    // anonymous (private) working area

// these functions can be put anywhere but we'll keep it here for the meantime
std::any example_function( Domain::Session::SessionBase & session, const std::vector<std::string> & args ) {
  return {"Hello World"};
}


namespace Domain::Session
{
  SessionBase::SessionBase( const std::string & description, const UserCredentials & credentials ) : _credentials( credentials ), _name( description )
  {
    _logger << "Session \"" + _name + "\" being used and has been successfully initialized";
  }


  // FIXME
  //SessionBase::~SessionBase() noexcept
  //{
    //_logger << "Session \"" + _name + "\" shutdown successfully";
  //}




  std::vector<std::string> SessionBase::getCommands()
  {
    std::vector<std::string> availableCommands;
    availableCommands.reserve( _commandDispatch.size() );

    for( const auto & [command, function] : _commandDispatch ) availableCommands.emplace_back( command );

    return availableCommands;
  }




  std::any SessionBase::executeCommand( const std::string & command, const std::vector<std::string> & args )
  {
    std::string parameters;
    for( const auto & arg : args )  parameters += '"' + arg + "\"  ";
    //_logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

    auto it = _commandDispatch.find( command );
    if( it == _commandDispatch.end() )
    {
      std::string message = __func__;
      message += " attempt to execute \"" + command + "\" failed, no such command";

      //_logger << message;
      std::cout << message;
      throw BadCommand( message );
    }

    auto results = it->second( *this, args);

    if( results.has_value() )
    {
      // The type of result depends on function called.  Let's assume strings for now ...
      //_logger << "Responding with: \"" + std::any_cast<const std::string &>( results ) + '"';
      //std::cout << "Responding with: \"" + std::reinterpret_cast<std::string>( results ) + '"';
      std::cout << std::any_cast<const char*>(results) << std::endl;
    }

    return results;
  }

  // 2) Now map the above system events to roles authorized to make such a request.  Many roles can request the same event, and many
  //    events can be requested by a single role.
  ClientSession::ClientSession( const UserCredentials & credentials ) : SessionBase( "Client", credentials )
  {
    _commandDispatch = { {"Help",            help        },
                         {"Reset Account",   resetAccount},
                         {"Shutdown System", shutdown    } };
  }




  ClerkSession::ClerkSession( const UserCredentials & credentials ) : SessionBase( "Clek", credentials )
  {
    _commandDispatch = { 
                         //{"Help",          help        },
                         {"ExampleFunction",          example_function        },
                         {"Pay Fines",     payFines    },
                         {"Return Book",   returnBook  } };
  }

}    // namespace Domain::Session
