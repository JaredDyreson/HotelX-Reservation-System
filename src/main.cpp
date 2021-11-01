#include <iostream>
#include "../include/Technical/Persistence/credentials.hpp"
#include "../include/Technical/Persistence/database.hpp"

int main() {
  std::cout << "hey mom!" << std::endl;
  TechnicalServices::Persistence::credentials creds = TechnicalServices::Persistence::credentials("Hello", "World");
  std::cout << creds.getPassword() << std::endl;
  Domain::Actors::Person person = Domain::Actors::Person("Jared Dyreson", 22, 
                                                          Domain::Actors::Role::client, std::make_tuple("username", "password"));
  std::cout << person.getAge() << std::endl;

  TechnicalServices::Persistence::Database database = TechnicalServices::Persistence::Database();
  database.insertElement(&person);
  std::cout << database.size() << std::endl;
  return 0;
}
