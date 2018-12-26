#include "port.h"

#include <algorithm>

#include "ship.hpp"
#include "results.h"

void Port::addShip(Ship ship)
{
  if (queue.size() > 100){
    return;
  }
  if (ship.cargo->cur_amount + ship.amount >= ship.cargo->max_amount) {
    return;
  }
  ship.time_to_unload = fabs(unloadingSpeed) <= 0.0001 ? -1 : static_cast<int>(ship.amount / fabs(unloadingSpeed));
  for(Ship & s : queue) {
    ship.time_to_park += s.time_to_unload;
  }
  ship.rate = ship.countRate();
  queue.push_front(ship);
}

void Port::tick(Results & results){
  if (queue.size() <= 0){
    return;
  }
  // пересчёт рейтинга
  int ind = 0;
  for (Ship & sh : queue){
    sh.time_to_unload = fabs(unloadingSpeed) <= 0.0001 ? -1 : static_cast<int>(sh.amount / fabs(unloadingSpeed));
  }
  for (Ship & sh : queue){
    sh.time_in_queue += 1;
    sh.time_to_park = 0;
    for(auto s = queue.begin() + ind + 1; s != queue.end(); ++s){
      sh.time_to_park += (s->time_to_unload == -1) ? 0 : s->time_to_unload;
    }
    sh.time_to_park += (shipOnUnloading.time_to_unload == -1) ? 0 : shipOnUnloading.time_to_unload;
    sh.rate = sh.countRate();
    ind++;
  }

  // общение
  if (queue.size() > 0){
    for(size_t i = 0; i < queue.size() - 1; ++i){
      Ship * curr = &queue[i];
      Ship * next = &queue[i + 1];
      if(curr->rate > next->rate){
        if(next->countRate(curr->time_to_unload) < curr->rate){
          std::iter_swap(queue.begin() + i, queue.begin() + i + 1);
//          break;
          ++i;
        }
      }
    }
  }

  ind = 0;
  for (Ship & sh : queue){
    sh.time_to_park = 0;
    for(auto s = queue.begin() + ind + 1; s != queue.end(); ++s){
      sh.time_to_park += (s->time_to_unload == -1) ? 0 : s->time_to_unload;
    }
    sh.time_to_park += (shipOnUnloading.time_to_unload == -1) ? 0 : shipOnUnloading.time_to_unload;
    ind++;
  }

  // отправка на разгрузку
  if(!inUse){
    shipOnUnloading = queue.back();
    queue.pop_back();
    inUse = true;
  } else if (shipOnUnloading.time_to_unload <= 0){
    if (queue.size() == 0){
      return;
    }
    results.mid_time_of_waiting += shipOnUnloading.time_in_queue;
    results.koef_zagruzki.unloaded += 1;
    shipOnUnloading = queue.back();
    queue.pop_back();
  }
  shipOnUnloading.cargo->addAmount(unloadingSpeed);
  shipOnUnloading.time_to_unload -= unloadingSpeed;
}

void Port::dumb_tick(Results & results){
  if (queue.size() <= 0){
    return;
  }

  for (Ship & sh : queue){
    sh.time_in_queue += 1;
  }
  if(!inUse){
    shipOnUnloading = queue.back();
    queue.pop_back();
    inUse = true;
  } else if (shipOnUnloading.time_to_unload <= 0){
    if (queue.size() == 0){
      return;
    }
    results.mid_time_of_waiting += shipOnUnloading.time_in_queue;
    results.koef_zagruzki.unloaded += 1;
    shipOnUnloading = queue.back();
    queue.pop_back();
  }
  shipOnUnloading.cargo->addAmount(unloadingSpeed);
  shipOnUnloading.time_to_unload -= unloadingSpeed;
}
