#include <memory>    // unique_ptr

#include "../../../include/Technical/Logging/LoggerHandler.hpp"
#include "../../../include/Technical/Logging/SimpleLogger.hpp"
#include "../../../include/Technical/Persistence/PersistenceHandler.hpp"


namespace Technical::Logging
{
  std::unique_ptr<LoggerHandler> LoggerHandler::create( std::ostream & loggingStream )
  {
    auto & persistantData  = Technical::Persistence::PersistenceHandler::instance();
    auto   requestedLogger = persistantData["Component.Logger"];

    if( requestedLogger == "Simple Logger" ) return std::make_unique<SimpleLogger>( loggingStream );

    throw BadLoggerRequest( "Unknown Logger object requested: \"" + requestedLogger + "\"\n  detected in function " + __func__ );
  }
}    // namespace Technical::Logging

