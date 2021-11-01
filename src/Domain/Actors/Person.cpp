#include <string>
#include "../../../include/Domain/Actors/Person.hpp"
#include "../../../include/Technical/Persistence/credentials.hpp"

namespace Domain::Actors {

  Person::Person(std::string _name, int _age, Role _role, std::tuple<std::string, std::string> _credentials) {
    const auto [username, password] = _credentials;
    this->creds = TechnicalServices::Persistence::credentials(username, password);
    this->name = _name;
    this->age = _age;
    this->role = _role;
  }

  /*
   * Getters
  */

  std::string Person::getName() { return this->name; }

  int Person::getAge() { return this->age; }


  TechnicalServices::Persistence::credentials Person::getCredentials() { return this->creds; }

  Domain::Actors::Role Person::getRole() { return this->role; }

  /*
   * Setters
  */

  void Person::setName(std::string name) { this->name = name; }
  void Person::setAge(int age) { this->age = age; }
  void Person::setRole(Domain::Actors::Role role){ this->role = role; }
}
