#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <string>
#include "cargo_type.hpp"

class Ship{
public:
  Ship() = default;
  Ship(const std::string name_, const double wght, const CargoType * cargo_) :
    name(name_),
    amount(wght),
    time_in_queue(0),
    rate(0),
    time_to_unload(0),
    cargo(cargo_)
  {}

  std::string name;

  double amount;
  int time_in_queue;
  double rate;
  int time_to_unload;
  const CargoType * cargo;

  void countRate(){
    rate = amount * cargo->koefPorchi * cargo->importance;
    rate *= time_in_queue == 0 ? 1 : time_in_queue;
  }

  void print() const {
    std::cout << name << std::endl;
    std::cout << "time_in_queue: " << time_in_queue << std::endl;
    std::cout << "rate: " << rate << std::endl;
    std::cout << "time_to_unload: " << time_to_unload << std::endl;
    std::cout << "cargo" << std::endl;
    cargo->print();
    std::cout << "amount: " << amount << std::endl;
  }
};

#endif // CARGO_TYPE_HPP
