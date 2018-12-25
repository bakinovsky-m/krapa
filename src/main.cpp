#include <iostream>
#include <vector>
#include <random>
#include <cmath>

#include "cargo_type.hpp"
#include "port.h"
#include "ship.hpp"

using namespace std;

void tickCargoTypes(vector<CargoType> & ct){
  for (CargoType & c:ct){
    c.tick();
  }
}

int main()
{
  vector<CargoType> ct{};
  // random na max_amount
  ct.push_back(CargoType("nasvay", 1.01, 100, 7, 1, 7));
  ct.push_back(CargoType("carrot", 1.23, 1000, 200, 1, 12));
  Port p{};
  p.addShip(Ship("nasvay bringer", 2, &ct[0]));
  p.addShip(Ship("carrot for poor rabbits", 12, &ct[1]));
  p.addShip(Ship("fucking carrot", 17, &ct[1]));

  default_random_engine eng(1);
  normal_distribution<double> intensity{};
  normal_distribution<double> port_speed(1, 1);

  int a = 0;
  while(!p.time_to_stop){
    p.unloadingSpeed = fabs(ceil(port_speed(eng)));
    if (fabs(intensity(eng)) > 0.99) {
      p.addShip(Ship("asd", 1, &ct[0]));
    }
    cout << endl << "AFTER " << a << " TICK" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "port speed: " << p.unloadingSpeed << endl;
    tickCargoTypes(ct);
    p.tick();
    p.print();
    a++;
    cin.get();
  }

  return 0;
}
