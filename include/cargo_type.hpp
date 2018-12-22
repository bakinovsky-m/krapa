#ifndef CARGO_TYPE_HPP
#define CARGO_TYPE_HPP

#include <string>
#include <iostream>

class CargoType{
public:
  CargoType() = default;
  CargoType(std::string name_, double kp, double imp) : 
    name(name_),
    koefPorchi(kp),
    importance(imp)
  {}
  
  std::string name;
  double koefPorchi;
  double importance;

  void print() const {
    std::cout << "name: " << name << std::endl;
    std::cout <<  "koefPorchi: " << koefPorchi << std::endl;
    std::cout << "importance: " << importance << std::endl;
  }
};

#endif // CARGO_TYPE_HPP
