#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <string>
#include "cargo_type.hpp"

class Ship{
public:
  Ship() = default;
  Ship(const std::string name_, const double wght, const int time_in_query_,
       const double rate_, CargoType * cargo_) :
    name(name_),
    amount(wght),
    time_in_query(time_in_query_),
    rate(rate_),
    time_to_unload(0),
    cargo(cargo_)
  {}

  std::string name;

  double amount;
  int time_in_query;
  double rate;
  int time_to_unload;
  CargoType * cargo;

  void countRate(){
    rate = amount * cargo->koefPorchi * cargo->importance * time_in_query;
  }

  void print() const {
    std::cout << "amount: " << amount << std::endl;
    cargo->print();
    std::cout << "time_in_query: " << time_in_query << std::endl;
    std::cout << "rate: " << rate << std::endl;
    std::cout << "time_to_unload: " << time_to_unload << std::endl;
  }
};

#endif // CARGO_TYPE_HPP
