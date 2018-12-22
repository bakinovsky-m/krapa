#ifndef PORT_H
#define PORT_H

#include <iostream>
#include <vector>
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
    inUse(false)
  {}
  void addShip(Ship ship);
  void tick();
  
  std::vector<Ship> queue;
  double unloadingSpeed;
  Ship shipOnUnloading;
  bool inUse;
  // типы

  void print() const {
    std::cout << "SHIPS IN QUEUE" << std::endl;
    for(Ship s : queue){
      s.print();
    }
    if(inUse){
      std::cout << "SHIP ON UNLOADING" << std::endl;
      shipOnUnloading.print();
    }
  }
};

#endif // PORT_H