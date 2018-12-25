#include "port.h"

#include "ship.hpp"

void Port::addShip(Ship ship)
{
  ship.time_to_unload = static_cast<int>(ship.amount / unloadingSpeed);
  ship.countRate();
  queue.push_back(ship);
}

void Port::tick(){
  for (Ship & sh : queue){
    sh.time_in_queue += 1;
    sh.countRate();
  }
  if(!inUse){
    shipOnUnloading = *queue.begin();
    queue.erase(queue.begin());
    inUse = true;
  } else if (shipOnUnloading.time_to_unload == 0){
    shipOnUnloading = *queue.begin();
    queue.erase(queue.begin());
  }
  shipOnUnloading.time_to_unload -= 1;
}
