#pragma once
#include <string>

namespace TechnicalServices::Persistence {
  class credentials {
    public:

      //credentials() {}; // must be here to satiate the default constructor called in Person.creds
      credentials();

      credentials(std::string, std::string);
      std::string getUserName();

      std::string getPassword();

      bool operator<(const credentials& src) const {
        /*
         * Not sure where to place this
        */
          return (this->username < src.username &&
                  this->password < src.password
                 );
      }

    private:
      std::string username;
      std::string password;
  };

}

