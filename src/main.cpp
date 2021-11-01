#include <iostream>
#include "../include/Technical/Persistence/credentials.hpp"
#include "../include/Domain/Actors/Person.hpp"

int main() {
  std::cout << "hey mom!" << std::endl;
  TechnicalServices::Persistence::credentials creds = TechnicalServices::Persistence::credentials("Hello", "World");
  std::cout << creds.getPassword() << std::endl;
  Domain::Actors::Person person = Domain::Actors::Person("Jared Dyreson", 22, 
                                                          Domain::Actors::Role::client, std::make_tuple("username", "password"));
  std::cout << person.getAge() << std::endl;
  return 0;
}
