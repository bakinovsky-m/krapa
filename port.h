#ifndef PORT_H
#define PORT_H

#include <vector>

class Ship;

class Port
{
public:
  Port();
  void addShip(Ship ship);
  
  std::vector<Ship> queue;
  double unloadingSpeed;
  // типы
};

#endif // PORT_H