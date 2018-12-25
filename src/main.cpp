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
  ct.push_back(CargoType("carrot", 0.92, 2));
  Port p{};
  p.addShip(Ship("nasvay bringer", 2, &ct[0]));
  p.addShip(Ship("carrot for poor rabbits", 12, &ct[1]));

  cout << "BEFORE TICK" << endl;
  p.print();

  p.tick();
  cout << endl << "AFTER 1 TICK" << endl;
  p.print();

  p.tick();
  cout << endl << "AFTER 2 TICK" << endl;
  p.print();

  p.tick();
  cout << endl << "AFTER 3 TICK" << endl;
  p.print();
  return 0;
}
