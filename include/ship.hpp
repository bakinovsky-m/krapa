#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <string>
#include "cargo_type.hpp"

class Ship{
public:
  Ship() = default;
  Ship(const std::string name_, const double wght, CargoType * cargo_) :
    name(name_),
    amount(wght),
    time_in_queue(0),
    rate(0),
    time_to_unload(0),
    time_to_park(0),
    cargo(cargo_)
  {}

  std::string name;

  int amount;
  int time_in_queue;
  double rate;
  int time_to_unload;
  int time_to_park;
  CargoType * cargo;

  double countRate(int extra_time=0){
    double ret = cargo->koefPorchi * (time_in_queue + time_to_park + extra_time);
    ret += amount * cargo->importance * cargo->time_with_no_supplies;
    return ret;
  }

  void print() const {
    std::cout << name << std::endl;
    std::cout << "time_in_queue: " << time_in_queue << std::endl;
    std::cout << "rate: " << rate << std::endl;
    std::cout << "time_to_park: " << time_to_park << std::endl;
    std::cout << "time_to_unload: " << time_to_unload << std::endl;
    std::cout << "amount on ship: " << amount << std::endl;
    std::cout << "cargo" << std::endl;
    cargo->print();
  }
};

#endif // CARGO_TYPE_HPP
