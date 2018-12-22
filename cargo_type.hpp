#ifndef CARGO_TYPE_HPP
#define CARGO_TYPE_HPP

#include <string>

class CargoType{
public:
  CargoType(std::string name_, double kp, double imp) : 
    name(name_),
    koefPorchi(kp),
    importance(imp)
  {}
  
  std::string name;
  double koefPorchi;
  double importance;
};

#endif // CARGO_TYPE_HPP
