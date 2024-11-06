#include "include/Greeter.h"

Greeter::Greeter(const std::string& name): name_(name) {}

std::string Greeter::greet() const {
  return "Hello, " + name_ + "!";
}