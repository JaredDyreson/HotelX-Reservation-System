#include <string>
#include "../../../include/Technical/Persistence/credentials.hpp"

namespace TechnicalServices::Persistence {
  credentials::credentials() {};
  credentials::credentials(std::string _user, std::string _pass) {
      this->username = _user;
      this->password = _pass;
  }
  std::string credentials::getUserName() { return this->username; }
  std::string credentials::getPassword() { return this->password; }


}
