#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "credentials.hpp"

#define roomStatus void // change this later
#define Statement std::string // change this later

namespace Technical::Persistence::DataClasses {
  /*
   * All of these classes are supposed to represent
   * key concepts in the program but we're less interested in
   * the actual functionality but these are vessels of information
   *
   * Therefore, we are also using structs instead of classes directly
   * because we just want these to contain data
  */

  enum PaymentType {PAYPAL, CASH, DEBIT};

  enum room_status {CLEAN, DIRTY, OCCUPIED, FREE};

  class _Statement {
    public:
      _Statement(std::string n, std::string s, std::string e, float a) : name(n), start(s), end(e), amountPaid(a) {}
    private:
      std::string name;
      std::string start;
      std::string end;
      float amountPaid;
  };

  class Payment {
      public:
        Payment(float a, std::string pr, std::string e, std::string n, PaymentType p) : amount(a), provider(pr), expirationDate(e), number(n), paymentType(p){}
      private:
        float amount;
        std::string provider;
        std::string expirationDate;
        std::string number;
        PaymentType paymentType;
  };

  class Reservation {
    private:
      std::string date;
      int number;
  };

  class memberShipInformation {
    public:
      memberShipInformation(std::string n, std::string d, std::vector<std::string> v, int p) : name(n), dateJoined(d), rewards(v), points(p) {}
    private:
      std::string name;
      std::string dateJoined;
      std::vector<std::string> rewards;
      int points;
  };



};
