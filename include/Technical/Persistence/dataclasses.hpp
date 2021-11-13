#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "credentials.hpp"

#define roomStatus void // change this later
#define Statement std::string // change this later

class sessionID {
    private:
      std::unique_ptr<std::string> session_id; // temp
};

namespace payment {
  enum PaymentType {PAYPAL, CASH, DEBIT};

  class Payment {
      public:
        Payment(float, std::string, std::string, std::string, PaymentType);
      private:
        float amount;
        std::string provider;
        std::string expirationDate;
        std::string number;
        PaymentType paymentType;
  };
}

namespace Technical::Persistence::DataClasses {
  /*
   * All of these classes are supposed to represent
   * key concepts in the program but we're less interested in
   * the actual functionality but these are vessels of information
   *
   * Therefore, we are also using structs instead of classes directly
   * because we just want these to contain data
  */

  class Person {
    public:
      Person(std::string, int, int);
      virtual void terminateSession(sessionID) = 0; 
    private:
      std::string name;
      int age;
      int position;
  };

  class Client : public Person {

    using Person::Person; // use the same constructor

    public:
      void terminateSession(sessionID);
  };

  class Clerk : public Person {
    using Person::Person;
    public:
      sessionID authenticateUser(std::string, std::string);
      //roomStatus setRoomStatus(int, roomStatus);
      float generateBill(std::string, int);
      Statement payBill(std::string, payment::Payment, float, int);
      void terminateSession(sessionID);
      size_t obtainGuestRoom(std::string, int);
  };


}
