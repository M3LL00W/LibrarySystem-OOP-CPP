#include "Date.h"
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;

Date::Date() : day(1), month(1), year(1970) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

Date Date::today() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

int Date::daysBetween(const Date& other) const {
    tm a = {0,0,0, day, month - 1, year - 1900};
    tm b = {0,0,0, other.day, other.month - 1, other.year - 1900};
    time_t x = mktime(&a);
    time_t y = mktime(&b);
    constexpr int secondsPerDay = 60 * 60 * 24;
    return static_cast<int>(difftime(y, x) / secondsPerDay);
}

string Date::toString() const {
    ostringstream oss;
    oss << setw(2) << setfill('0') << day << '/'
        << setw(2) << setfill('0') << month << '/'
        << year;
    return oss.str();
}

Date Date::fromString(const string& dateStr) {
    int d, m, y;
    sscanf(dateStr.c_str(), "%d/%d/%d", &d, &m, &y);
    return Date(d,m,y);
}

ostream& operator<<(std::ostream& os, const Date& date) {
    os << std::setw(2) << setfill('0') << date.day << '/'
       << std::setw(2) << setfill('0') << date.month << '/'
       << date.year;
    return os;
}

Date Date::addDays(int days) const {
    tm t = {0};
    t.tm_mday = day + days;
    t.tm_mon = month - 1;
    t.tm_year = year - 1900;
    mktime(&t);  // normalizes date (adjusts day/month/year overflow)
    return Date(t.tm_mday, t.tm_mon + 1, t.tm_year + 1900);
}

