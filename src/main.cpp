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
  ct.push_back(CargoType("carrot", 1.23, 1000, 20, 2, 12));
  ct.push_back(CargoType("nasvay", 1.01, 1000, 7, 1, 9));
  Port p{};
  p.addShip(Ship("nasvay bringer", 2, &ct[0]));
//  p.addShip(Ship("carrot for poor rabbits", 12, &ct[1]));
//  p.addShip(Ship("fucking carrot", 17, &ct[1]));

  default_random_engine eng_for_intensity(1);
  default_random_engine eng_for_port_speed = default_random_engine(2);
  random_device eng_for_cargo_type{};
  normal_distribution<double> intensity{};
  normal_distribution<double> port_speed(1, 1);
  uniform_int_distribution<int> cargo_type_index(0, ct.size() - 1);

  default_random_engine eng_for_amount_int = default_random_engine(5);
  uniform_int_distribution<int> amount_int(1, 3);

  default_random_engine eng_for_amount = default_random_engine(6);
  uniform_int_distribution<int> amount_(1, 100);

  double full_amount = 0;
  double mid_index = 0;
  int ships = 0;

  int a = 0;
  while(!p.time_to_stop && a < 1000){
    p.unloadingSpeed = fabs(ceil(port_speed(eng_for_port_speed)));
    if (fabs(intensity(eng_for_intensity)) > 0.5) {
      double q = cargo_type_index(eng_for_cargo_type);
      int qwe = (int)round(q);
      mid_index += q;
      int asd = amount_int(eng_for_amount_int) * 100 + amount_(eng_for_amount);
      p.addShip(Ship("asd", asd, &ct[qwe]));
      full_amount = (full_amount + asd);
      ships++;
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
  cout << "mid amount: " << full_amount/p.queue.size() << endl;
  cout << "mid index: " << mid_index/p.queue.size() << endl;
  cout << "ships: " << ships << endl;

  return 0;
}
