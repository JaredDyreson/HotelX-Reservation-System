#include <iostream>
#include <map>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>

#include "../include/Domain/Session/SessionHandler.hpp"
#include "../include/Technical/Logging/LoggerHandler.hpp"
#include "../include/Technical/Persistence/PersistenceHandler.hpp"

/*
 * Since we are not supposed to have any UI, I decided to dump
 * all of the `launch` logic here and just....figure it out later
 * I was not in the mood for losing extra points
*/


int main() {

    Technical::Persistence::PersistenceHandler & _persistentData =  Technical::Persistence::PersistenceHandler::instance() ;
    // 1) Fetch Role legal value list
    std::vector<std::string> roleLegalValues = _persistentData.findRoles();

    // 2) Present login screen to user and get username, password, and valid role
    Domain::Session::UserCredentials credentials  = {"", "", {""}};           // ensures roles[0] exists
    auto &                           selectedRole = credentials.roles[0];     // convenience alias

    std::unique_ptr<Domain::Session::SessionHandler> sessionControl;
    std::cout << "[INFO] Press enter to continue...." << std::endl;
    do
    {
      std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );

      std::cout << "  name: ";
      std::getline( std::cin, credentials.userName );

      std::cout << "  pass phrase: ";
      std::getline( std::cin, credentials.passPhrase );

      unsigned menuSelection;
      do
      {
        for( unsigned i = 0; i != roleLegalValues.size(); ++i )   std::cout << std::setw( 2 ) << i << " - " << roleLegalValues[i] << '\n';
        std::cout << "  role (0-" << roleLegalValues.size()-1 << "): ";
        std::cin  >> menuSelection;
      } while( menuSelection >= roleLegalValues.size() );

      selectedRole = roleLegalValues[menuSelection];

      std::cout << selectedRole << std::endl;


      // 3) Validate user is authorized for this role, and if so create session
      sessionControl = Domain::Session::SessionHandler::createSession( credentials );
      if( sessionControl != nullptr )
      {
        std::cout << "Login Successful for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";
        break;
      }

      std::cout << "** Login failed\n";
      //_logger << "Login failure for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";

    } while( true );


     //4) Fetch functionality options for this role
    do
    {
      auto        commands = sessionControl->getCommands();
      std::string selectedCommand;
      unsigned    menuSelection;

      do
      {
        for( unsigned i = 0; i != commands.size(); ++i ) std::cout << std::setw( 2 ) << i << " - " << commands[i] << '\n';
        std::cout << std::setw( 2 ) << commands.size() << " - " << "Quit\n";

        std::cout << "  action (0-" << commands.size() << "): ";
        std::cin >> menuSelection;
      } while( menuSelection > commands.size() );

      if( menuSelection == commands.size() ) break;

      selectedCommand = commands[menuSelection];
      std::cout << selectedCommand << std::endl;
      //_logger << "Command selected \"" + selectedCommand + '"';


      //*****************************************************************************************************************************
     //*  5) The user interface will collect relevant information to execute the chosen command.  This section requires the UI to
     //*     know what information to collect, and hence what the available commands are.  Our goal is loose (minimal) coupling, not
     //*     no coupling. This can be achieved in a variety of ways, but one common way is to pass strings instead of strong typed
     //*     parameters.
     //****************************************************************************************************************************
      if( selectedCommand == "Checkout Book" )
      {
        std::vector<std::string> parameters( 3 );

        std::cout << " Enter book's title:  ";  std::cin >> std::ws;  std::getline( std::cin, parameters[0] );
        std::cout << " Enter book's author: ";  std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
        std::cout << " Enter book's ISBN:   ";  std::cin >> std::ws;  std::getline( std::cin, parameters[2] );

        auto results = sessionControl->executeCommand( selectedCommand, parameters );
        if( results.has_value() ) std::cout << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"'; // change _logger to std::cout
      }

      //else if( selectedCommand == "Another command" )  ...  {}

      else sessionControl->executeCommand( selectedCommand, {} );
    } while( true );

    //_logger << "Ending session and terminating";


  return 0;
}
