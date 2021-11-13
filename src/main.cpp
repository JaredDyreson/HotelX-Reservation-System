#include <iostream>
#include "../include/Technical/Persistence/credentials.hpp"

int main() {
  std::cout << "hey mom!" << std::endl;
  TechnicalServices::Persistence::credentials creds = TechnicalServices::Persistence::credentials("Hello", "World");

  std::cout << creds.getPassword() << std::endl;
  return 0;
}
