#include <iostream>
#include <vector>

using namespace std;

#include "cargo_type.hpp"
#include "port.h"
#include "ship.hpp"

int main()
{
  vector<CargoType> ct{};
  ct.push_back(CargoType("nasvay", 0.99, 0.7));
  Port p{};
  p.addShip(Ship("a", 123, 0, 1, &ct[0]));
  p.print();
  p.tick();
  p.print();
  ct[0].importance = 123;
  p.print();
  return 0;
}
