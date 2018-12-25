#ifndef PORT_H
#define PORT_H

#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include "ship.hpp"
//class Ship;

class Port
{
public:
  Port():
    queue(),
    unloadingSpeed(1),
    shipOnUnloading(),
    inUse(false),
    time_to_stop(false)
  {}
  void addShip(Ship ship);
  void tick();
  void dumb_tick();

  std::deque<Ship> queue;
  double unloadingSpeed;
  Ship shipOnUnloading;
  bool inUse;
  bool time_to_stop;

  void print() const {
    std::cout << "SHIPS IN QUEUE" << std::endl;
    for(Ship s : queue){
      std::cout << "---------" << std::endl;
      s.print();
    }
    if(inUse){
      std::cout << std::endl;
      std::cout << "SHIP ON UNLOADING" << std::endl;
      std::cout << "---------" << std::endl;
      shipOnUnloading.print();
    }
  }
};

#endif // PORT_H
