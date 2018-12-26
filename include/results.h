#ifndef RESULTS_H
#define RESULTS_H

struct KoefZagruzki{
  int come = 0;
  int unloaded = 0;
  double mid = 0;
  int count = 0;
  double get() const {
    return mid/count;
  }
};

struct Results {
  KoefZagruzki koef_zagruzki{};
  double mid_len_of_queue = 0;
  double mid_time_of_waiting = 0;
  double score = 0;
};
#endif // RESULTS_H
