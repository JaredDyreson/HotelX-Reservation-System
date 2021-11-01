#include "Window.hpp"

/*
 * NOTE: 
 * Not sure why I have to define all the functions in
 * the class' hpp file and they do not automatically populate, this kinda sucks but ok
*/

class CLIWindow : public Window {
  public:
    CLIWindow(std::string);
    ~CLIWindow();
    void display();
    void setTitle(std::string);
    std::string getTitle();

  private:
    std::string title;
};
