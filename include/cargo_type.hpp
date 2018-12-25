#ifndef CARGO_TYPE_HPP
#define CARGO_TYPE_HPP

#include <string>
#include <iostream>
#include <cmath>

class CargoType{
public:
  CargoType() = default;
  CargoType(const std::string name_,
            const double koefPorchi_,
            const int max_amount_,
            const int cur_amount_,
            const int speed_of_usage_,
            const double default_need_) :
    name(name_),
    koefPorchi(koefPorchi_),
    importance(0),
    max_amount(max_amount_),
    cur_amount(cur_amount_),
    speed_of_usage(speed_of_usage_),
    default_need(default_need_),
    time_with_no_supplies(0)
  {}

  std::string name;
  double koefPorchi;
  double importance;

  int max_amount;
  int cur_amount;
  int speed_of_usage; // in amount in tick
  double default_need;
  int time_with_no_supplies;

  void tick() {
    if(cur_amount <= 0){
      importance = default_need;
      return;
    }
    cur_amount -= speed_of_usage;

    if(cur_amount <= 0) {
      cur_amount = 0;
      time_with_no_supplies++;
    }
    importance = fabs((double)max_amount/cur_amount);
  }

  void addAmount(int add) {
    cur_amount += add;
    time_with_no_supplies = 0;
  }

  void print() const {
    std::cout << "name: " << name << std::endl;
    std::cout << "koefPorchi: " << koefPorchi << std::endl;
    std::cout << "importance: " << importance << std::endl;
    std::cout << "amount in port: " << cur_amount << "/" << max_amount << std::endl;
  }
};

#endif // CARGO_TYPE_HPP
