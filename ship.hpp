#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>
#include "cargo_type.hpp"
#include "port.h"


class Ship{
public:
  Ship(std::string name_, double wght, int time_in_query_,
       double rate_, CargoType cargo_, Port port_) :
    name(name_),
    weight(wght),
    time_in_query(time_in_query_),
    rate(rate_),
    cargo(cargo_),
    port(port_)
  {}

  std::string name;
  CargoType cargo;

  Port port;
  double weight;
  int time_in_query;
  double rate;
  int time_to_unload;

  void countRate();
  void countTimeToUnload();
  void stepInQuery();

};

void Ship::countTimeToUnload()
{
    time_to_unload = int(weight / port.unloadingSpeed);
}

void Ship::stepInQuery()
{
    time_in_query++;
}


void Ship::countRate()
{
    rate = weight * cargo.koefPorchi * cargo.importance * time_in_query;
}





#endif // CARGO_TYPE_HPP
