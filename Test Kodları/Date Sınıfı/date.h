#ifndef DATE_H
#define DATE_H

#include <iosfwd>
#include <ctime>

class Date {
public:
    static constexpr int year_base = 1900;
    static constexpr int random_min_year = 1940;
    static constexpr int random_max_year = 2020;
    enum class WeekDay {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

    Date();
    Date(int d, int m, int y);
    Date(const char *p);
    Date(std::time_t timer);
    int get_month_day()const;
    int get_month()const;
    int get_year()const;
    int get_year_day()const;

    WeekDay get_week_day()const;

    Date& set_month_day(int day);
    Date& set_month(int month);
    Date& set_year(int year);
    Date& set(int day, int mon, int year);
    Date operator-(int day)const;
    Date& operator+=(int day);
    Date& operator-=(int day);
    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);

    static Date random_date();
    static constexpr bool isleap(int y);

    friend bool operator<(const Date &, const Date &);

    friend std::ostream &operator<<(std::ostream &os, const Date &date);
    friend std::istream &operator>>(std::istream &is, Date &date);

    friend int operator-(const Date &d1, const Date &d2);
    friend std::ostream& operator<<(std::ostream& os, const Date::WeekDay& wd);
private:
    int md;
    int mm;
    int my;
};

int operator-(const Date &d1, const Date &d2);

inline bool operator<(const Date& lhs, const Date& rhs)
{
    return (lhs.my < rhs.my) ? true : ((lhs.my > rhs.my) ? false : ((lhs.mm < rhs.mm) ?
     true : ((lhs.mm > rhs.mm) ? false : ((lhs.md < rhs.md) ? true : false))));
}

inline bool operator<=(const Date& x, const Date& y)
{
    return !(y<x);
}

inline bool operator>(const Date& x, const Date& y)
{
    return y<x;
}

inline bool operator>=(const Date& x, const Date& y)
{
    return !(x<y);
}

inline bool operator==(const Date& x, const Date& y)
{
    return !(x<y) && !(y<x);
}

inline bool operator!=(const Date& x, const Date& y)
{
    return !(x==y);
}

inline Date operator+(const Date &date, int n)
{
    return Date{date}.operator+=(n);
}

inline Date operator+(int n, const Date& date)
{
    return Date{date}+n;
}

inline Date::WeekDay& operator++(Date::WeekDay &wd)
{
    return wd = (wd == Date::WeekDay::Saturday) ? Date::WeekDay::Sunday : static_cast<Date::WeekDay>((static_cast<int>(wd)+1));
}

inline Date::WeekDay operator++(Date::WeekDay &wd, int)
{
    Date::WeekDay temp{wd};
    ++wd;
    return temp;
}

inline Date::WeekDay& operator--(Date::WeekDay &wd)
{
    return wd = (wd == Date::WeekDay::Sunday) ? Date::WeekDay::Saturday : static_cast<Date::WeekDay>((static_cast<int>(wd)-1));
}

inline Date::WeekDay operator--(Date::WeekDay &wd, int){
    Date::WeekDay temp{wd};
    --wd;
    return temp;
}

#endif // DATE_H
