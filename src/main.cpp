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
  // TODO: random na max_amount
  ct.push_back(CargoType("nasvay", 1.01, 100, 7, 1, 7));
  ct.push_back(CargoType("carrot", 1.23, 1000, 200, 1, 12));
  Port p{};
  p.addShip(Ship("nasvay bringer", 2, &ct[0]));
//  p.addShip(Ship("carrot for poor rabbits", 12, &ct[1]));
//  p.addShip(Ship("fucking carrot", 17, &ct[1]));

  default_random_engine eng_for_intensity(1);
  default_random_engine eng_for_port_speed = default_random_engine(2);
  default_random_engine eng_for_cargo_amount = default_random_engine(3);
  default_random_engine eng_for_cargo_type = default_random_engine(4);
  normal_distribution<double> intensity{};
  normal_distribution<double> port_speed(1, 1);
  normal_distribution<double> amount{};
  uniform_int_distribution<int> cargo_type_index(0, ct.size() - 1);

  int a = 0;
  while(!p.time_to_stop && a < 1000){
    p.unloadingSpeed = fabs(ceil(port_speed(eng_for_port_speed)));
    if (fabs(intensity(eng_for_intensity)) > 0.99) {
      int qwe = round(cargo_type_index(eng_for_cargo_type));
      p.addShip(Ship("asd", round(fabs(amount(eng_for_cargo_amount)) * 10), &ct[qwe]));
    }
//    cout << endl << "AFTER " << a << " TICK" << endl;
//    cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
//    cout << "port speed: " << p.unloadingSpeed << endl;
    tickCargoTypes(ct);
    p.tick();
//    p.dumb_tick();
//    p.print();
    a++;
//    cin.get();
  }

  cout << "on tick " << a << endl;
  for(auto c : ct) {
    cout << c.name << ": " << c.cur_amount << "/" << c.max_amount << endl;
  }

  return 0;
}
