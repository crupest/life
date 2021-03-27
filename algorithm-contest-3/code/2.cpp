#include <algorithm>
#include <cstdio>
#include <vector>

int ConvertYear(int x) {
  if (x >= 60)
    return 1900 + x;
  return 2000 + x;
}

bool CheckMonth(int x) {
  if (x <= 0 && x >= 13) {
    return false;
  }

  return true;
}

bool IsLeapYear(int y) {
  if (y == 2000)
    return false;
  if (y % 4)
    return false;
  return true;
}

int days[] = {0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool CheckDay(int day, int month, int year) {
  if (month == 2) {
    const bool leap = IsLeapYear(year);
    if (leap) {
      return day >= 1 && day <= 29;
    } else {
      return day >= 1 && day <= 28;
    }
  }

  return day >= 1 && day <= days[month];
}

struct Date {
  int year;
  int month;
  int day;
};

bool operator==(const Date &l, const Date &r) {
  return l.year == r.year && l.month == r.month && l.day == r.day;
}

bool operator<(const Date &l, const Date &r) {
  if (l.year < r.year)
    return true;
  else if (l.year > r.year)
    return false;
  else if (l.month < r.month)
    return true;
  else if (l.month > r.month)
    return false;
  else if (l.day < r.day)
    return true;
  return false;
}

bool Check(int year, int month, int day, Date *result) {
  if (!CheckMonth(month))
    return false;
  const auto y = ConvertYear(year);
  if (!CheckDay(day, month, y))
    return false;

  result->year = y;
  result->month = month;
  result->day = day;
  return true;
}

int main() {
  std::vector<Date> results;

  int a, b, c;
  std::scanf("%d/%d/%d", &a, &b, &c);

  Date temp;
  if (Check(a, b, c, &temp)) {
    results.push_back(temp);
  }

  if (Check(c, a, b, &temp)) {
    results.push_back(temp);
  }

  if (Check(c, b, a, &temp)) {
    results.push_back(temp);
  }

  results.erase(std::unique(results.begin(), results.end()), results.end());
  std::sort(results.begin(), results.end());

  for (const auto &r : results) {
    std::printf("%d-%02d-%02d\n", r.year, r.month, r.day);
  }

  return 0;
}
