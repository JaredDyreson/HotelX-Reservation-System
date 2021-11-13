#pragma once
#include <string>

namespace Technical::Persistence {
  enum Role { CLERK, CLIENT };

  class credentials {
    public:

      //credentials() {}; // must be here to satiate the default constructor called in Person.creds
      credentials();

      credentials(std::string, std::string);
      std::string getUserName();

      std::string getPassword();
      Role getRole() const;

    private:
      std::string username;
      std::string password;
      Role role;
  };

}

