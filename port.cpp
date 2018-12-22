#include "port.h"

#include "ship.hpp"

void Port::addShip(Ship ship)
{
  queue.push_back(ship);
}

