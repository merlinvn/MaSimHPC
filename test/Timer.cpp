//
// Created by Nguyen Tran on 6/13/18.
//

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

// Obtained from: http://howardhinnant.github.io/date_algorithms.html

auto create_timepoint(int years, int months, int days) {
  //perform checks, do division, modulus and stuff...
  years -= 1900; //epoch
  std::tm date = {};
  date.tm_year = years;
  date.tm_mon = months;
  date.tm_mday = days;

  return std::chrono::system_clock::from_time_t(std::mktime(&date));
}


template<typename Clock, typename Duration>
std::ostream &operator<<(std::ostream &os, const std::chrono::time_point<Clock, Duration> &timep) {
  auto converted_timep = Clock::to_time_t(timep);
  os << std::put_time(std::localtime(&converted_timep), "%d %b %Y");
  return os;
}


// Returns number of days since civil 1970-01-01.  Negative values indicate
//    days prior to 1970-01-01.
// Preconditions:  y-m-d represents a date in the civil (Gregorian) calendar
//                 m is in [1, 12]
//                 d is in [1, last_day_of_month(y, m)]
//                 y is "approximately" in
//                   [numeric_limits<Int>::min()/366, numeric_limits<Int>::max()/366]
//                 Exact range of validity is:
//                 [civil_from_days(numeric_limits<Int>::min()),
//                  civil_from_days(numeric_limits<Int>::max()-719468)]
template<typename Int>
constexpr Int days_from_civil(Int y, unsigned m, unsigned d) noexcept {
  static_assert(std::numeric_limits<unsigned>::digits >= 18,
                "This algorithm has not been ported to a 16 bit unsigned integer");
  static_assert(std::numeric_limits<Int>::digits >= 20,
                "This algorithm has not been ported to a 16 bit signed integer");
  y -= m <= 2;
  const Int era = (y >= 0 ? y : y - 399) / 400;
  const unsigned yoe = static_cast<unsigned>(y - era * 400);      // [0, 399]
  const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;  // [0, 365]
  const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;         // [0, 146096]
  return era * 146097 + static_cast<Int>(doe) - 719468;
}

// Returns year/month/day triple in civil calendar
// Preconditions:  z is number of days since 1970-01-01 and is in the range:
//                   [numeric_limits<Int>::min(), numeric_limits<Int>::max()-719468].
template<typename Int>
constexpr std::tuple<Int, unsigned, unsigned> civil_from_days(Int z) noexcept {
  static_assert(std::numeric_limits<unsigned>::digits >= 18,
                "This algorithm has not been ported to a 16 bit unsigned integer");
  static_assert(std::numeric_limits<Int>::digits >= 20,
                "This algorithm has not been ported to a 16 bit signed integer");
  z += 719468;
  const Int era = (z >= 0 ? z : z - 146096) / 146097;
  const unsigned doe = static_cast<unsigned>(z - era * 146097);          // [0, 146096]
  const unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;  // [0, 399]
  const Int y = static_cast<Int>(yoe) + era * 400;
  const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100);                // [0, 365]
  const unsigned mp = (5 * doy + 2) / 153;                                   // [0, 11]
  const unsigned d = doy - (153 * mp + 2) / 5 + 1;                             // [1, 31]
  const unsigned m = mp + (mp < 10 ? 3 : -9);                            // [1, 12]
  return std::tuple<Int, unsigned, unsigned>(y + (m <= 2), m, d);
}


template<typename To, typename Rep, typename Period>
To round_down(const std::chrono::duration<Rep, Period> &d) {
  To t = std::chrono::duration_cast<To>(d);
  if (t > d)
    --t;
  return t;
}

// Returns day of week in civil calendar [0, 6] -> [Sun, Sat]
// Preconditions:  z is number of days since 1970-01-01 and is in the range:
//                   [numeric_limits<Int>::min(), numeric_limits<Int>::max()-4].
template<typename Int>
constexpr unsigned weekday_from_days(Int z) noexcept {
  return static_cast<unsigned>(z >= -4 ? (z + 4) % 7 : (z + 5) % 7 + 6);
}


template<typename Clock, typename Duration>
std::tm make_utc_tm(const std::chrono::time_point<Clock, Duration> &tp) {
  using namespace std;
  using namespace std::chrono;
  typedef duration<int, ratio_multiply<hours::period, ratio<24>>> days;
  // t is time duration since 1970-01-01
  Duration t = tp.time_since_epoch();
  // d is days since 1970-01-01
  days d = round_down<days>(t);
  // t is now time duration since midnight of day d
  t -= d;
  // break d down into year/month/day
  int year;
  unsigned month;
  unsigned day;
  std::tie(year, month, day) = civil_from_days(d.count());
  // start filling in the tm with calendar info
  std::tm tm = {0};
  tm.tm_year = year - 1900;
  tm.tm_mon = month - 1;
  tm.tm_mday = day;
  tm.tm_wday = weekday_from_days(d.count());
  tm.tm_yday = d.count() - days_from_civil(year, 1, 1);
  // Fill in the time
  tm.tm_hour = duration_cast<hours>(t).count();
  t -= hours(tm.tm_hour);
  tm.tm_min = duration_cast<minutes>(t).count();
  t -= minutes(tm.tm_min);
  tm.tm_sec = duration_cast<seconds>(t).count();
  return tm;
}


template<typename Clock, typename Duration>
int get_date_in_month(const std::chrono::time_point<Clock, Duration> &tp) {
  using namespace std;
  using namespace std::chrono;
  typedef duration<int, ratio_multiply<hours::period, ratio<24>>> days;
  // t is time duration since 1970-01-01
  Duration t = tp.time_since_epoch();
  // d is days since 1970-01-01
  days d = round_down<days>(t);
  // t is now time duration since midnight of day d
  t -= d;
  // break d down into year/month/day
  int year;
  unsigned month;
  unsigned day;
  std::tie(year, month, day) = civil_from_days(d.count());

  return day;
}

template<typename Clock, typename Duration>
bool is_first_day_of_month(const std::chrono::time_point<Clock, Duration> &point) {
  return get_date_in_month(point) == 1;
}


int total_time = 15000;


int main() {

//1991 Jan 1 === create_timepoint(1991, 0, 1);
  const int start_year = 1991;
  // Jan is 0
  const int start_month = 5;

  for (int current_time = 0; current_time < total_time; ++current_time) {
    auto calendar_date = create_timepoint(start_year, start_month, current_time);

    if (is_first_day_of_month(calendar_date)) {
      std::cout << calendar_date << "\t";
      std::cout << std::chrono::system_clock::to_time_t(calendar_date) << "\t" << current_time << std::endl;
    }
  }
  return 0;
}
