#include "date.h"
#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include <istream>
#include <iomanip>
#include <random>

constexpr static const char delimeter = ' ';
constexpr static int pmonthDays[][13] = {{0,31,28,31,30,31,30,31,31,30,31,30,31},
{0,31,29,31,30,31,30,31,31,30,31,30,31}};


constexpr bool Date::is_valid(int day, int month, int year) {
    // int x = Date::isleap(year) ? 1 : 0;
    // if(day<1||day>pmonthDays[x][month]) {
    //     std::cerr << "Day is not correct number\n";
    //     return false;
    // }
    // else if(month < 1 || month > 12) {
    //     std::cerr << "Month is not correct number\n";
    //     return false;
    // }
    // else if(year < Date::year_base) {
    //     std::cerr << "Year is not correct number\n";
    //     return false;
    // }
    // return true;
    return year > Date::year_base ? ((day >= 1 && day <= pmonthDays[(int)isleap(year)][month]) ?
        (month >= 1 && month <= 12) : false) : false;
}

Date::Date(): Date(1,1,1900) //Delegating ctor
{

}

Date::Date(int d, int m, int y) : md(d), mm(m), my(y)
{
    if(is_valid(md,mm,my)) {
        exit(EXIT_FAILURE);
    };
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
    auto ltm = std::localtime(&timer);
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
    int x = isleap(my);
    while(temp--) {
        ans += pmonthDays[x][temp];
    }
    return ans;
}

Date::WeekDay Date::get_week_day() const
{
    //Doomsday Rule implementation
    static constexpr int doomsdayArrayLeapYear[] = {0,4,1,7,4,2,6,4,1,5,3,7,5};
    static constexpr int doomsdayArrayNotLeapYear[] = {0,3,7,7,4,2,6,4,1,5,3,7,5};

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
    if(day < 0 || day > pmonthDays[isleap(my)][mm])
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
    return *this;
}

Date& Date::set(int day, int mon, int year)
{
    if(is_valid(day,mon,year)) {
        md = day;
        mm = mon;
        my = year;
        return *this;
    }
    //throw bad_date{};
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
    int x = isleap(my);
    int temp = pmonthDays[x][mm];
    while(total_day > temp) {
        if(mm>11) {
            mm = 0;
            ++my;
            x = isleap(my);
        }
        temp += pmonthDays[x][++mm];
    }
    md = pmonthDays[x][mm] - (temp - total_day);
    return *this;
}

Date& Date::operator-=(int day)
{
    if(day<0) {
        return operator+=(-day);
    }

    int total_day = md-day;

    int x = isleap(my);

    while(total_day < 0) {
        if(mm<2) {
            mm = 13;
            --my;
            x = isleap(my);
        }
        total_day += pmonthDays[x][--mm];
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
    ++(*this);
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
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

std::ostream& operator<<(std::ostream &os, const Date &date)
{
    using namespace std;
    static const char* const pdays[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    
    ostringstream ossr;
    ossr << setfill('0') << setw(2) << date.md;
    ossr << setfill(' ') << left;
    ossr << " " << pmonthDays[date.mm] << " " << date.my << " " << pdays[static_cast<int>(date.get_week_day())];
}

Date Date::random_date() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution1(random_min_year,random_max_year);
    std::uniform_int_distribution<int16_t> distribution2(1,12);
    int year = distribution1(generator);  // generates number in the range 1..6 
    int month = distribution2(generator);
    std::uniform_int_distribution<int> distribution3(0,(pmonthDays[isleap(year)][month]));
    int day = distribution3(generator);
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
