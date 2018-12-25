#include <iostream>
#include <vector>

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
  ct.push_back(CargoType("nasvay", 1.01, 100, 7, 1, 7));
  ct.push_back(CargoType("carrot", 1.23, 1000, 200, 1, 12));
  Port p{};
  p.addShip(Ship("nasvay bringer", 2, &ct[0]));
  p.addShip(Ship("carrot for poor rabbits", 12, &ct[1]));
  p.addShip(Ship("fucking carrot", 17, &ct[1]));

  cout << "BEFORE TICK" << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
  p.print();
  for (CargoType & c:ct){
    cout << c.name << ": " << c.cur_amount << "/" << c.max_amount << endl;
  }

  tickCargoTypes(ct);
  p.tick();
  cout << endl << "AFTER 1 TICK" << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
  p.print();

  tickCargoTypes(ct);
  p.tick();
  cout << endl << "AFTER 2 TICK" << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
  p.print();

  tickCargoTypes(ct);
  p.tick();
  cout << endl << "AFTER 3 TICK" << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
  p.print();

  int a = 4;
  while(!p.time_to_stop){
    cout << endl << "AFTER " << a << " TICK" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
    tickCargoTypes(ct);
    p.tick();
    p.print();
    a++;
  }

  return 0;
}
