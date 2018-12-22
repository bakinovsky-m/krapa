#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>
#include "cargo_type.hpp"

class Ship{
public:
  Ship(std::string name_, double wght, int time_in_query_, double rate_, CargoType cargo_) :
    name(name_),
    weight(wght),
    time_in_query(time_in_query_),
    rate(rate_),
    cargo_type(cargo_)
  {}

  std::string name;
  CargoType cargo_type;

  double weight;
  int time_in_query;
  double rate;


  void CountRate();
};


void Ship::CountRate()
{

    rate = weight * cargo_type.koefPorchi * cargo_type.importance * time_in_query;

}





#endif // CARGO_TYPE_HPP
