#include "Date.h"
#include <iomanip>

using namespace std;


Date::Date(int day, int month, int year) {
    if (year < 1900) {
        cout << "Not support for date before 1900" << endl;
        return;
    }

    tm time_in = {0, 0, 0, day, /* second, minute, hour, 1-based day */
    month - 1, year - 1900 };   /* 0-based month, year since 1900    */

    this->rawtime = mktime(&time_in);
    this->time = localtime(&(this->rawtime));
}
Date::Date(time_t rawtime) {
    this->rawtime = rawtime;
    this->time = localtime(&(this->rawtime));
}
Date::~Date() {
    delete(this->time);
    return;
}


int Date::getDay() {
    return this->time->tm_mday;
}
int Date::getMonth() {
    return this->time->tm_mon + 1;
}
int Date::getYear() {
    return this->time->tm_year + 1900;
}


void Date::setDay(int day) {
    this->time->tm_mday = day;
    this->rawtime = mktime(this->time);
}
void Date::setMonth(int month) {
    this->time->tm_mon = month - 1;
    this->rawtime = mktime(this->time);
}
void Date::setYear(int year) {
    if (year < 1900) {
        cout << "Not support for date before 1900" << endl;
        return;
    }
    this->time->tm_year = year - 1900;
    this->rawtime = mktime(this->time);
}


Date Date::DateAfter(int days) {
    tm* new_time = localtime(&(this->rawtime));
    new_time->tm_mday += days;
    
    return Date(mktime(new_time));
}


Date Date::DateBefore(int days) {
    tm* new_time = localtime(&(this->rawtime));
    new_time->tm_mday -= days;
    
    return Date(mktime(new_time));
}


string Date::dayOfWeek() {
    return weekday[this->time->tm_wday];
}


int Date::numberOfDays() {
    /* if year % 4 = 0 and month = 2, than go to numberOfDays_array[12] */
    return numberOfDays_array[ (this->getYear() % 4) | (this->getMonth() - 2) 
                               ? this->time->tm_mon 
                               : 12 ];
}


void Date::printMonthCalendar() {
    cout << endl << endl
         << "        " << setw(9) << right << month[this->getMonth() - 1] 
         << "  " << this->getYear() << endl;
    cout << "---------------------------------" << endl;
    cout << "Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;
    cout << "---------------------------------" << endl;

    /* get the day of first day of month */
    int first_day = (this->time->tm_wday - (this->getDay() % 7) + 8) % 7;
    int day = 1;

    /* first row */
    for(int col = 0; col < 7; col++) {
        if (col < first_day) {
            cout << "     ";
        } else {
            cout << setw(5) << left << day++;
        }
    }
    cout << endl;

    /* other rows */
    for(int row = 1; row < 6; row++) {
        for(int col = 0; col < 7; col++) {
            cout << setw(5) << left << day++;
            if (day > this->numberOfDays()) {
                cout << endl;
                return;
            }
        }
        cout << endl;
    }
}
