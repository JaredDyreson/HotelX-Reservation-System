#pragma once

#include "../../../include/Domain/Session/Session.hpp" // ignore std::any error
#include "../../../include/Technical/Persistence/credentials.hpp"

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

// these functions can be put anywhere but we'll keep it here for the meantime
std::any example_function( Domain::Session::SessionBase & session, const std::vector<std::string> & args ) {
  return {"Hello World"};
}

enum roomStatus {CLEAN, DIRTY, OCCUPIED, FREE};
enum PaymentType {PAYPAL, CASH, DEBIT};

struct Statement {
  std::string name;
  std::string start;
  std::string end;
  float amountPaid;
  Statement(std::string n, std::string s, std::string e, float a) : name(n), start(s), end(e), amountPaid(a) {}
};

class Reservation {
  public:
    Reservation(std::string, int);
  private:
    std::string date;
    int number;
};

class Payment {
  public:
    Payment(float a, std::string p, std::string e, std::string n, PaymentType pa) : amount(a), provider(p), expirationDate(e), number(n), paymentType(pa) {}
  private:
    float amount;
    std::string provider;
    std::string expirationDate;
    std::string number;
    PaymentType paymentType;
};



roomStatus _setRoomStatus(int roomNumber, roomStatus status) {
  // do some internal database work, just return the given status
  std::cout << "[INFO | LOGGER] setting the room status" << std::endl;
  return status;
}
size_t _obtainRoomCode(std::string username, int roomNmber) {
  // generically return a room code, please implement in further iterations
  return 5361;
}

float _generateBill(std::string username, int room_number) {

  // TODO
  return 100.50;
}

Statement payBill(std::string username, Payment method, float amount, int room_number) {
  return Statement(
      "Jared",
      "01/01/2021",
      "01/03/2021",
      amount
  );
}

/*
 * Check in Guest FUNCTIONS BOOTSTRAPPED
*/

std::any obtainGuestRoom( Domain::Session::SessionBase & session, const std::vector<std::string> & args ) {
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
    std::string room_stat;
    std::string room_number;
    std::cout << "What is their room number: ";
    std::getline(std::cin, room_number);

    std::cout << "What is the room status: ";
    std::getline(std::cin, room_stat);

    if(room_stat == "Occupied") {
      return roomStatus::OCCUPIED;
    }
    return roomStatus::FREE;
}

std::any obtainRoomCode( Domain::Session::SessionBase & session, const std::vector<std::string> & args ) { 
    std::string name;
    std::cout << "What is their name: ";
    std::getline(std::cin, name);

    std::string room_number;
    std::cout << "What is their room number: ";
    std::getline(std::cin, room_number);

    return {5361};
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
      //std::cout << std::any_cast<const char*>(results) << std::endl;
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
                         {"Help",          help        },
                         {"Set Room Status",          setRoomStatus        },
                         {"Obtain Room Code",          obtainRoomCode        },
                         {"Obtain Guest Room",          obtainGuestRoom} };
  }

    void ClerkSession::hello_world_function() {
      std::cout << "hello world!" << std::endl;
    }

}
