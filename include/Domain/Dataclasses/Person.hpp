#include <string>
#include <tuple>
#include "../../../include/Technical/Persistence/credentials.hpp"

namespace Domain::Actors {

  enum class Role { client, clerk, sysadmin };

  class Person {
    public:
    Person(std::string /* name */ , int /* age */, Role role , std::tuple<std::string/* username */, std::string> /* password */);
    std::string getName();
    int getAge();
    Role getRole();
    Technical::Persistence::credentials getCredentials();

    void setName(std::string);
    void setAge(int);
    void setRole(Role);


    bool operator<(const Person& src) const {
      // This is for the database
      return this->age < src.age;
    }

  private:
    int age;
    std::string name;
    Role role;
    Technical::Persistence::credentials creds;
  };
};
