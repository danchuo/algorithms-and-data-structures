#include <iostream>
#include <string>
using std::string;

string WhenSoundAlarm(const string &current_time, const string &interval);

void SplitLineToInt(const string &interval, int *hours_in_interval,
                    int *minutes_in_interval, int *seconds_in_interval);

void ReduceByMod(int *first_step, int *second_step, int by);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  string current_time;
  string interval;

  std::getline(std::cin, current_time);
  std::getline(std::cin, interval);

  std::cout << WhenSoundAlarm(current_time, interval);
  return 0;
}

void SplitLineToInt(const string &interval, int *hours_in_interval,
                    int *minutes_in_interval, int *seconds_in_interval) {
  int colons_in_interval = 0;

  for (char i : interval) {
    if (i == ':') {
      ++colons_in_interval;
    }
  }

  switch (colons_in_interval) {
    case 0: {
      *hours_in_interval = 0;
      *minutes_in_interval = 0;
      *seconds_in_interval = std::stoi(interval);
      break;
    }
    case 1: {
      *hours_in_interval = 0;
      *minutes_in_interval = std::stoi(interval);
      *seconds_in_interval = std::stoi(interval.substr(interval.find_first_of(':') + 1));
      break;
    }
    default: {
      *hours_in_interval = std::stoi(interval);
      *minutes_in_interval = std::stoi(interval.substr(interval.find_first_of(':') + 1));
      *seconds_in_interval = std::stoi(interval.substr(interval.find_last_of(':') + 1));
      break;
    }
  }
}

string WhenSoundAlarm(const string &current_time, const string &interval) {
  int days = 0;
  int hours_in_interval = 0;
  int minutes_in_interval = 0;
  int seconds_in_interval = 0;
  int hours_in_answer = 0;
  int minutes_in_answer = 0;
  int seconds_in_answer = 0;

  SplitLineToInt(current_time, &hours_in_answer, &minutes_in_answer, &seconds_in_answer);
  SplitLineToInt(interval, &hours_in_interval, &minutes_in_interval, &seconds_in_interval);

  seconds_in_answer += seconds_in_interval;
  ReduceByMod(&seconds_in_answer, &minutes_in_answer, 60);

  minutes_in_answer += minutes_in_interval;
  ReduceByMod(&minutes_in_answer, &hours_in_answer, 60);

  hours_in_answer += hours_in_interval;
  ReduceByMod(&hours_in_answer, &days, 24);

  string answer = (hours_in_answer > 9 ?
                   std::to_string(hours_in_answer) :
                   ("0" + std::to_string(hours_in_answer)))
      + ":" +
      (minutes_in_answer > 9 ?
       std::to_string(minutes_in_answer) :
       ("0" + std::to_string(minutes_in_answer)))
      + ":" +
      (seconds_in_answer > 9 ?
       std::to_string(seconds_in_answer) :
       ("0" + std::to_string(seconds_in_answer)));

  if (days > 0) {
    answer += "+" + std::to_string(days) + " days";
  }

  return answer;
}

void ReduceByMod(int *first_step, int *second_step, int by) {
  if (*first_step >= by) {
    *second_step += *first_step / by;
    *first_step %= by;
  }
}

