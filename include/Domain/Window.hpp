#include <string>

/*
 * Pure virtual Window class
 * to be used in various scenarios
*/

class Window {
  public:
    Window(std::string);
    virtual ~Window() {  }
    virtual void display() = 0;
    virtual void setTitle(std::string) = 0;
    virtual std::string getTitle() = 0;

  protected:
    std::string title;
};
