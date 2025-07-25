#pragma once
#include <string>
using namespace std;

class Date {
public:
    int day;
    int month;
    int year;

    Date();
    Date(int d, int m, int y);
    Date addDays(int days) const;


    static Date today();  // Returns current system date

    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;

    int daysBetween(const Date& other) const;

    string toString() const;
    static Date fromString(const string& dateStr);
};
ostream& operator<<(ostream& os, const Date& date);