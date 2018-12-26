#include <iostream>
#include <vector>
#include <random>
#include <cmath>

#include "cargo_type.hpp"
#include "port.h"
#include "ship.hpp"
#include "results.h"

using namespace std;

// количество товара на складе +
// коэффициент загрузки системы
// средняя длина очереди (среднее число заявок в очереди) +
// среднее время ожидания обслуживания +
// оценка удовлетворенности порта по предложенной метрике +

void tickCargoTypes(vector<CargoType> & ct){
  for (CargoType & c:ct){
    c.tick();
  }
}

Results simulate(Port p, vector<CargoType> & ct, int ticks) {
  default_random_engine eng_for_intensity(1);
  default_random_engine eng_for_port_speed = default_random_engine(2);
  random_device eng_for_cargo_type{};
  normal_distribution<double> intensity{};
  normal_distribution<double> port_speed(1, 1);
  uniform_int_distribution<int> cargo_type_index(0, ct.size() - 1);

  default_random_engine eng_for_amount_int = default_random_engine(5);
  uniform_int_distribution<int> amount_int(1, 3);

  default_random_engine eng_for_amount = default_random_engine(6);
  uniform_int_distribution<int> amount_(1, 10);

  Results results {};

  int a = 0;
  int ships = 0;
  while(!p.time_to_stop && a < ticks){
    p.unloadingSpeed = fabs(ceil(port_speed(eng_for_port_speed)));
    if (fabs(intensity(eng_for_intensity)) > 0.5) {
      double q = cargo_type_index(eng_for_cargo_type);
      int qwe = static_cast<int>(round(q));
      int asd = amount_int(eng_for_amount_int) * 10 + amount_(eng_for_amount);
      ships++;
      results.koef_zagruzki.come += 1;
      p.addShip(Ship("asd", asd, &ct[qwe]));
    }
    tickCargoTypes(ct);
    p.tick(results);

    results.mid_len_of_queue += p.queue.size();

    a++;
  }

  double score = 0;
  for(auto c:ct){
    score += (double)c.cur_amount/c.max_amount;
  }
  score /= ct.size();
  results.score = score;
  results.mid_len_of_queue /= a;
  results.mid_time_of_waiting /= ships;
  return results;
}

Results dumb_simulate(Port p, vector<CargoType> & ct, int ticks) {
  default_random_engine eng_for_intensity(1);
  default_random_engine eng_for_port_speed = default_random_engine(2);
  random_device eng_for_cargo_type{};
  normal_distribution<double> intensity{};
  normal_distribution<double> port_speed(1, 1);
  uniform_int_distribution<int> cargo_type_index(0, ct.size() - 1);

  default_random_engine eng_for_amount_int = default_random_engine(5);
  uniform_int_distribution<int> amount_int(1, 3);

  default_random_engine eng_for_amount = default_random_engine(6);
  uniform_int_distribution<int> amount_(1, 10);

  Results results{};

  int a = 0;
  int ships = 0;
  while(!p.time_to_stop && a < ticks){
    p.unloadingSpeed = fabs(ceil(port_speed(eng_for_port_speed)));
    if (fabs(intensity(eng_for_intensity)) > 0.5) {
      double q = cargo_type_index(eng_for_cargo_type);
      int qwe = static_cast<int>(round(q));
      int asd = amount_int(eng_for_amount_int) * 10 + amount_(eng_for_amount);
      results.koef_zagruzki.come += 1;
      ships++;
      p.addShip(Ship("asd", asd, &ct[qwe]));
    }
    tickCargoTypes(ct);
    p.dumb_tick(results);
    results.mid_len_of_queue += p.queue.size();
    a++;
  }

  double score = 0;
  for(auto c:ct){
    score += (double)c.cur_amount/c.max_amount;
  }
  score /= ct.size();
  results.score = score;
  results.mid_len_of_queue /= a;
  results.mid_time_of_waiting /= ships;
  return results;
}

int main(){
  int times = 50;
  double mid_tick_score = 0;
  double mid_len_of_queue = 0;
  double mid_time_in_queue = 0;
  double mid_koef_zagruzki = 0;

  double mid_dumb_tick_score = 0;
  double mid_dumb_len_of_queue = 0;
  double mid_dumb_time_in_queue = 0;
  double mid_dumb_koef_zagruzki = 0;
  for (int i = 0; i < times; ++i) {
    vector<CargoType> ct{};
    ct.push_back(CargoType("carrot", 1.23, 1000, 20, 2, 1000));
    ct.push_back(CargoType("nasvay", 1.01, 1000, 7, 1, 1000));
    Port p{};
    p.addShip(Ship("nasvay bringer", 2, &ct[0]));
    Results results = simulate(p, ct, 1000);
    mid_tick_score += results.score;
    mid_len_of_queue += results.mid_len_of_queue;
    mid_time_in_queue += results.mid_time_of_waiting;
    mid_koef_zagruzki += results.koef_zagruzki.get();
  }
  for (int i = 0; i < times; ++i) {
    vector<CargoType> ct{};
    ct.push_back(CargoType("carrot", 1.23, 1000, 20, 2, 1000));
    ct.push_back(CargoType("nasvay", 1.01, 1000, 7, 1, 1000));
    Port p1{};
    p1.addShip(Ship("nasvay bringer", 2, &ct[0]));
    Results results = dumb_simulate(p1, ct, 1000);
    mid_dumb_tick_score += results.score;
    mid_dumb_len_of_queue += results.mid_len_of_queue;
    mid_dumb_time_in_queue += results.mid_time_of_waiting;
    mid_dumb_koef_zagruzki += results.koef_zagruzki.get();
  }
  cout << "------------" << endl;
  cout << "tick: " <<endl;
  cout <<"score: " << mid_tick_score/times << endl;
  cout <<"mid len: " << mid_len_of_queue/times << endl;
  cout <<"mid time in queue: " << mid_time_in_queue/times << endl;
  cout <<"mid koef zagruzki: " << mid_koef_zagruzki/times << endl;
  cout << "dumb tick: " << endl;
  cout <<"score: " << mid_dumb_tick_score/times << endl;
  cout <<"mid len: " << mid_dumb_len_of_queue/times << endl;
  cout <<"mid time in queue: " << mid_dumb_time_in_queue/times << endl;
  cout <<"mid koef zagruzki: " << mid_dumb_koef_zagruzki/times << endl;

}
