#pragma once

#include "../../../include/Domain/Session/Session.hpp" // ignore std::any error
#include "../../../include/Technical/Persistence/credentials.hpp"
#include "../../../include/Technical/Persistence/dataclasses.hpp"

#include <any>
#include <limits>
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

/*
 * CLERK FUNCTIONS BEGIN
*/

std::any obtainGuestRoom( Domain::Session::SessionBase & session, const std::vector<std::string> & args ) {
    std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );
    std::string name;
    std::string reservation_number;
    std::string reservation_date;
    std::cout << "What is their name: ";
    std::getline(std::cin, name);

    std::cout << "What is their reservation number: ";
    std::getline(std::cin, reservation_number);
    std::cout << "What is their reservation date: ";
    std::getline(std::cin, reservation_date);
    // std::stoi(reservation_number)
    return {100};
}

std::any setRoomStatus( Domain::Session::SessionBase & session, const std::vector<std::string> & args ) { 
    std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );
    std::string room_stat;
    std::string room_number;
    std::cout << "What is their room number: ";
    std::getline(std::cin, room_number);

    std::cout << "What is the room status: ";
    std::getline(std::cin, room_stat);

    if(room_stat == "Occupied") {
      return Technical::Persistence::DataClasses::room_status::OCCUPIED;
    }
    return Technical::Persistence::DataClasses::room_status::FREE;
}

std::any obtainRoomCode( Domain::Session::SessionBase & session, const std::vector<std::string> & args ) { 
    std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );
    std::string name;
    std::cout << "What is their name: ";
    std::getline(std::cin, name);

    std::string room_number;
    std::cout << "What is their room number: ";
    std::getline(std::cin, room_number);
    std::cout << "ROOM CODE IS: 5361" << std::endl;

    return {5361};
}

std::any payBill( Domain::Session::SessionBase & session, const std::vector<std::string> & args ) { 
  std::cout << "PAYING BILL FOR JARED" << std::endl;

  std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );
  std::string name;
  std::string provider;
  std::string number;
  std::string expiration_date;

  std::cout << "What is their name: ";
  std::getline(std::cin, name);

  std::cout << "What is their provider: ";
  std::getline(std::cin, provider);

  std::cout << "What is their card number: ";
  std::getline(std::cin, number);

  std::cout << "What is their card expiration date: ";
  std::getline(std::cin, expiration_date);

  Technical::Persistence::DataClasses::Payment(100.50, provider, number, expiration_date, Technical::Persistence::DataClasses::PaymentType::DEBIT);

  return {Technical::Persistence::DataClasses::_Statement(
      "Jared",
      "01/01/2021",
      "01/03/2021",
      100.50
  )};
}

std::any generateBill( Domain::Session::SessionBase & session, const std::vector<std::string> & args ) { 

  std::cout << "GENERATING BILIL OF 100.50 FOR JARED" << std::endl;
  return (float)100.50;
}

/*
 * END CLERK FUNCTIONS
*/

/*
 * BEGIN CLIENT FUNCTIONS
*/

std::any requestMembershipInformation( Domain::Session::SessionBase & session, const std::vector<std::string> & args ) { 

    std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );
    std::string name;
    std::cout << "What is their name: ";
    std::getline(std::cin, name);
    
    // parse information better

    std::cout << "date joined: 01/01/1970, you have a free night stay and you have 100 points" << std::endl;

    return {
      Technical::Persistence::DataClasses::memberShipInformation(name, "01/01/1970", {"Free Night Stay!"}, 100)
    };
}

std::any requestPaymentInformation( Domain::Session::SessionBase & session, const std::vector<std::string> & args ) { 
    std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );

    std::string name;

    std::cout << "What is their name: ";
    std::getline(std::cin, name);

    std::cout << "Visa, 123-133 04/33 DEBIT" << std::endl;
    return { 
      Technical::Persistence::DataClasses::Payment(0, "Visa", "123-133", "04/33", Technical::Persistence::DataClasses::PaymentType::DEBIT)};
}


std::any updatePaymentInformation( Domain::Session::SessionBase & session, const std::vector<std::string> & args ) { 

    std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );

    std::string name;
    std::string provider;
    std::string number;
    std::string expiration_date;

    std::cout << "What is their name: ";
    std::getline(std::cin, name);

    std::cout << "What is their provider: ";
    std::getline(std::cin, provider);

    std::cout << "What is their card number: ";
    std::getline(std::cin, number);

    std::cout << "What is their card expiration date: ";
    std::getline(std::cin, expiration_date);

    std::cout << provider << " " << number << " " << expiration_date << " " << std::endl;

    Technical::Persistence::DataClasses::Payment(0, provider, number, expiration_date, Technical::Persistence::DataClasses::PaymentType::DEBIT);
    return 0;
}

/*
 * END CLIENT FUNCTIONS
*/

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

    return results;
  }

  // 2) Now map the above system events to roles authorized to make such a request.  Many roles can request the same event, and many
  //    events can be requested by a single role.
  ClientSession::ClientSession( const UserCredentials & credentials ) : SessionBase( "Client", credentials )
  {
    _commandDispatch = { {"Help",            help        },
                         {"Request Memeberhip Information",   requestMembershipInformation},
                         {"Request Payment Information",   requestPaymentInformation},
                         {"Update Payment Information",   updatePaymentInformation},
                         {"Shutdown System", shutdown    } };
  }




  ClerkSession::ClerkSession( const UserCredentials & credentials ) : SessionBase( "Clek", credentials )
  {
    _commandDispatch = { 
                         {"Help",          help        },
                         {"Set Room Status",          setRoomStatus        },
                         {"Obtain Room Code",          obtainRoomCode        },
                         {"Generate Bill",          generateBill        },
                         {"Pay Bill",                    payBill        },
                         {"Obtain Guest Room",          obtainGuestRoom} };
  }

    void ClerkSession::hello_world_function() {
      std::cout << "hello world!" << std::endl;
    }

}
