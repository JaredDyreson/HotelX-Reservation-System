#include <iostream>
#include <string>

class Window {
 public:
  Window(std::string);
  virtual std::string getTitle() = 0;
  virtual void setTitle(std::string) = 0;

 private:
  std::string title;
};
