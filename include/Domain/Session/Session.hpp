#pragma once
#include <map>
#include <any>
#include <vector>

#include "./SessionHandler.hpp" // ignore std::any error, you're smoking crack
#include "../../../include/Technical/Persistence/credentials.hpp"

namespace Domain::Session
{
  class SessionBase : public SessionHandler
  {
    public:
      SessionBase( const std::string & description,  const Technical::Persistence::credentials & credentials );

      // Operations
      std::vector<std::string> getCommands   () override;    // retrieves the list of actions (commands)
      std::any                 executeCommand( const std::string & command, const std::vector<std::string> & args ) override;    // executes one of the actions retrieved


      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      //~SessionBase() noexcept override = 0;

  protected: 
  public:  // Dispatched functions need access to these attributes, so for now make these public instead of protected
    // Types
    using DispatchTable = std::map<std::string, std::any (*)( Domain::Session::SessionBase &, const std::vector<std::string> & )>;
    friend class Policy;

    // Instance Attributes (TODO: include logger)
    //std::unique_ptr<Technical::Logging::LoggerHandler> _loggerPtr = Technical::Logging::LoggerHandler::create();
    //Technical::Logging::LoggerHandler &                _logger    = *_loggerPtr;

    Technical::Persistence::credentials const                                      _credentials;
    std::string     const                                      _name      = "Undefined";
    DispatchTable                                              _commandDispatch;
  };    // class SessionBase


  struct AdministratorSession : SessionBase{ AdministratorSession( const Technical::Persistence::credentials & credentials ); };
  struct BorrowerSession      : SessionBase{ BorrowerSession     ( const Technical::Persistence::credentials & credentials ); };
  struct LibrarianSession     : SessionBase{ LibrarianSession    ( const Technical::Persistence::credentials & credentials ); };
  struct ManagementSession    : SessionBase{ ManagementSession   ( const Technical::Persistence::credentials & credentials ); };

} // namespace Domain::Session
