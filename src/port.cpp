#include "port.h"

#include <algorithm>

#include "ship.hpp"

void Port::addShip(Ship ship)
{
  ship.time_to_unload = static_cast<int>(ship.amount / unloadingSpeed);
  for(Ship & s : queue) {
    ship.time_to_park += s.time_to_unload;
  }
  ship.rate = ship.countRate();
  queue.push_front(ship);
}

void Port::tick(){
  // пересчёт рейтинга
  int ind = 0;
  for (Ship & sh : queue){
    sh.time_in_queue += 1;
    sh.time_to_park = 0;
    for(auto s = queue.begin() + ind + 1; s != queue.end(); ++s){
      sh.time_to_park += s->time_to_unload;
    }
    sh.time_to_park += shipOnUnloading.time_to_unload;
    sh.rate = sh.countRate();
    ind++;
  }

  // общение
  for(size_t i = 0; i < queue.size() - 1; ++i){
    Ship * curr = &queue[i];
    Ship * next = &queue[i + 1];
    if(curr->rate > next->rate){
      std::iter_swap(queue.begin() + i, queue.begin() + i + 1);
    }
  }

  ind = 0;
  for (Ship & sh : queue){
    sh.time_to_park = 0;
    for(auto s = queue.begin() + ind + 1; s != queue.end(); ++s){
      sh.time_to_park += s->time_to_unload;
    }
    sh.time_to_park += shipOnUnloading.time_to_unload - 1;
    ind++;
  }

  // отправка на разгрузку
  if(!inUse){
    queue.back().time_to_park = 0;
    shipOnUnloading = queue.back();
    queue.pop_back();
    inUse = true;
  } else if (shipOnUnloading.time_to_unload == 0){
    queue.back().time_to_park = 0;
    shipOnUnloading = queue.back();
    queue.pop_back();
  }
  shipOnUnloading.time_to_unload -= 1;
}
