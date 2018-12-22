#ifndef PORT_HPP
#define PORT_HPP

#include <vector>

#include "ship.hpp"

class Port {
public:
  Port() = default;
  
  void addShip(Ship ship){
    queue.push_back(ship);
  }
  
  std::vector<Ship> queue;
  double unloadingSpeed;
  // типы
};

#endif // PORT_HPP
