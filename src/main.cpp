#include <iostream>
#include <map>
#include "../include/Technical/Persistence/credentials.hpp"
#include "../include/Technical/Persistence/database.hpp"


int main() {
  std::cout << "hey mom!" << std::endl;
  std::map<std::string, std::string> _map = {
    {"Jared", "coffeerulz"},
    {"Hello", "World"}
  };

  Technical::Persistence::credentials creds = Technical::Persistence::credentials("Hello", "World");
  Technical::Persistence::DataBase::Database database = Technical::Persistence::DataBase::Database(_map);

  std::cout << creds.getPassword() << std::endl;
  return 0;
}
