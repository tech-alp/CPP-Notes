#include <iostream>
#include <string>
#include <sstream>

#include "date.h"

constexpr static const char delimeter = ' ';
static int pmonthDays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

Date::Date(): Date(1,1,1900) //Delegating ctor
{

}

Date::Date(int d, int m, int y) : md(d), mm(m), my(y)
{
    if(isleap(my)) {
        pmonthDays[2] = 29;
    } else {
        pmonthDays[2] = 28;
    }
    if(md<1||md>pmonthDays[mm]) {
        std::cerr << "Day is not correct number\n";
        exit(EXIT_FAILURE);
    }
    else if(mm < 1 || mm > 12) {
        std::cerr << "Month is not correct number\n";
        exit(EXIT_FAILURE);
    }
    else if(my < year_base) {
        std::cerr << "Year is not correct number\n";
        exit(EXIT_FAILURE);
    }
}

Date::Date(const char* p)
{
    std::string str{p};
    int day, month,year;
    char ch;

    std::stringstream ss;
    ss << str;
    ss >> day >> ch >> month >> ch >> year;

    set_year(year);
    set_month(month);
    set_month_day(day);
}

Date::Date(time_t timer)
{
    tm* ltm = localtime(&timer);
    set_year(year_base + ltm->tm_year);
    set_month(1+ltm->tm_mon);
    set_month_day(ltm->tm_mday);
}

int Date::get_month_day() const
{
    return md;
}

int Date::get_month() const
{
    return mm;
}

int Date::get_year() const
{
    return my;
}

int Date::get_year_day() const
{
    int ans = md,temp = mm;
    if(isleap(my)) {
        pmonthDays[2] = 29;
    }else {
        pmonthDays[2] = 28;
    }
    while(temp--) {
        ans += pmonthDays[temp];
    }
    return ans;
}

Date::WeekDay Date::get_week_day() const
{
    //Doomsday Rule implementation
    static const int doomsdayArrayLeapYear[] = {0,4,1,7,4,2,6,4,1,5,3,7,5};
    static const int doomsdayArrayNotLeapYear[] = {0,3,7,7,4,2,6,4,1,5,3,7,5};

    int year2Digits = my - ((int)(my / 100))*100;
    int calc1 = year2Digits/12;
    int calc2 = year2Digits - (calc1 * 12);
    int calc3 = calc2 / 4;
    int firstDigitYear = my / 1000;
    int anchorNum = (firstDigitYear==1) ? 3 : 2;
    int calc4 = calc1+calc2+calc3+anchorNum;
    int calc5 = calc4%7;
    int leapYear = isleap(my);
    int doomsdayDay, dayIndex;
    if(leapYear) {
        doomsdayDay = doomsdayArrayLeapYear[mm];
    } else {
        doomsdayDay = doomsdayArrayNotLeapYear[mm];
    }
    if(md < doomsdayDay) {
        dayIndex = calc5 - (doomsdayDay - md);
    } else if( md > doomsdayDay) {
        dayIndex = calc5 + (md - doomsdayDay);
        if(dayIndex > 7) {
            dayIndex %= 7;
        }
    } else {
        dayIndex = calc5;
    }

    if(dayIndex < 0) {
        dayIndex += 7;
    }

    return WeekDay(dayIndex);
}

Date& Date::set_month_day(int day)
{
    if(day < 0 || day > pmonthDays[mm])
    {
        std::cerr << "Please enter correct day\n";
        exit(EXIT_FAILURE);
    }
    md = day;
    return *this;
}

Date& Date::set_month(int month)
{
    if(month < 1 || month > 12)
    {
        std::cerr << "Please enter correct month\n";
        exit(EXIT_FAILURE);
    }
    mm = month;
    return *this;
}

Date& Date::set_year(int year)
{
    if(year < year_base)
    {
        std::cerr << "Please enter correct year\n";
        exit(EXIT_FAILURE);
    }
    my = year;
    if(isleap(year)) {
        pmonthDays[2] = 29;
    } else {
        pmonthDays[2] = 28;
    }
    return *this;
}

Date& Date::set(int day, int mon, int year)
{
    set_month_day(day);
    set_month(mon);
    set_year(year);
    return *this;
}

Date Date::operator-(int day) const
{
    return Date{*this}-=day;
}

Date& Date::operator+=(int day)
{
    if(day<0) {
        return operator-=(-day);
    }

    int total_day = md+day;
    int temp = pmonthDays[mm];
    if(isleap(my)) {
        pmonthDays[2] = 29;
    } else {
        pmonthDays[2] = 28;
    }
    while(total_day > temp) {
        if(mm>11) {
            mm = 0;
            ++my;
            if(isleap(my)) {
                pmonthDays[2] = 29;
            }else {
                pmonthDays[2] = 28;
            }
        }
        temp += pmonthDays[++mm];
    }
    md = pmonthDays[mm] - (temp - total_day);
    return *this;
}

Date& Date::operator-=(int day)
{
    if(day<0) {
        return operator+=(-day);
    }

    int total_day = md-day;
    if(isleap(my)) {
        pmonthDays[2] = 29;
    } else {
        pmonthDays[2] = 28;
    }

    while(total_day < 0) {
        if(mm<2) {
            mm = 13;
            --my;
            if(isleap(my)) {
                pmonthDays[2] = 29;
            }else {
                pmonthDays[2] = 28;
            }
        }
        total_day += pmonthDays[--mm];
    }
    md = total_day;
    return *this;
}

Date& Date::operator++()
{
    return (*this)+=1;
}

Date Date::operator++(int)
{
    Date temp{*this};
    (*this).operator+=(1);
    return temp;
}

Date& Date::operator--()
{
    return (*this).operator-=(1);
}

Date Date::operator--(int)
{
    Date temp{*this};
    --(*this);
    return temp;
}

constexpr bool Date::isleap(int year)
{
    if (year % 4 != 0) {
        return false;
    } else if (year % 400 == 0) {
        
        return true;
    } else if (year % 100 == 0) {
        
        return false;
    } else {
        return true;
    }
}

std::ostream &operator<<(std::ostream &os, const Date &date)
{
    static const char* const pdays[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    if(date.get_month_day() < 10) {
        os << '0';
    }
    os << date.get_month_day() << delimeter;
    if(date.get_month() < 10) {
        os << '0';
    }
    return os << date.get_month() << delimeter << date.get_year() << delimeter
              << pdays[static_cast<int>(date.get_week_day())];
}

Date Date::random_date() {
    srand(time(NULL));
    int day,month,year;
    year = (rand()%(random_max_year-random_min_year+1))+random_min_year;
    month = rand()%12+1;
    if(isleap(year)) {
        pmonthDays[2] = 29;
        day = rand()%(pmonthDays[month])+1;
    } else {
        pmonthDays[2] = 28;
        day = rand()%(pmonthDays[month])+1;
    }
    return Date{day,month,year};
}

std::istream& operator>>(std::istream &is, Date &date)
{
    static char temp;
    return is >> date.md >> temp >> date.mm >> temp >> date.my;
}

std::ostream& operator<<(std::ostream& os, const Date::WeekDay& wd)
{
    static const char* const pdays[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    return os << pdays[static_cast<int>(wd)];
}

int operator-(const Date &d1, const Date &d2)
{
    int total_day_d1 = d1.get_year_day()+d1.get_year()*365;
    int total_day_d2 = d2.get_year_day()+d2.get_year()*365;

    int total_day = total_day_d1-total_day_d2;

    if(total_day > 0) {
        for(int i = d1.get_year()+1; i < d2.get_year(); ++i) {
            if(Date::isleap(i))
                total_day += 1;
        }
    } else {
        for(int i = d2.get_year()+1; i < d1.get_year(); ++i) {
            if(Date::isleap(i))
                total_day -= 1;
        }
    }

    return total_day;
}
