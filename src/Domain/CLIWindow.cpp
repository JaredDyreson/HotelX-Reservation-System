#include <iostream>

#include "../../include/Domain/CLIWindow.hpp"

CLIWindow::CLIWindow(std::string title) : Window(title) {}
CLIWindow::~CLIWindow() {  }

void CLIWindow::setTitle(std::string title) {
  this->title = title;
}

std::string CLIWindow::getTitle() {
  return this->title;
}

void CLIWindow::display() {
  std::cout << "Displaying " << this-> title << std::endl;
}
