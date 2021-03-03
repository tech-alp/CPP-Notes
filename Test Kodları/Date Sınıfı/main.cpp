#include <ctime>
#include <iostream>

#include "date.h"

void test_randomDate() {
    while(true) {
        char ch;
        std::cout << "Enter the 'q' for quick: ";
        std::cin >> ch;
        Date date = Date::random_date();
        std::cout << "Random date = " << date << '\n';
        if(ch=='q')
            break;
    }
}

void test_operator_increment_decrement() {
    using namespace std;
    Date date{time(NULL)};
    cout << "current date = " << date << '\n';
    date--;
    cout << "yesterday date = " << date << '\n';
    ++date;
    ++date;
    cout << "tomorrow date = " << date << '\n';

    Date date2{time(NULL)};
    cout << "Today's date = " << date2 << '\n';
    int day = 719;
    cout << "today's day of year(" << date2.get_year_day() << ") + " << day << " gun = ";
    date2 += day;
    cout << date2 << '\n';

    cout << "day of year(" << date2.get_year_day() << ") - " << day << " gun = ";
    date2 -= day;
    cout << date2 << '\n';
}


void test_compare_operator() {
    using namespace std;
    Date date1{time(NULL)};
    Date date2 = Date::random_date();
    Date date3{"18-05-2021"};

//    Date date1,date2;
//    cout << "Enter the two days\n";
//    cin >> date1 >> date2;
    cout << "date1 = " << date1 << " " << "date2 = " << date2 << "date3 = " << date3 <<'\n';
    cout << boolalpha << "( " << date1 << " <  " << date2  << ") = " << (date1 < date2)  << '\n';
    cout << boolalpha << "( " << date1 << " <  " << date3  << ") = " << (date1 < date3)  << '\n';
    cout << boolalpha << "( " << date2 << " <  " << date3  << ") = " << (date2 < date3)  << '\n';
    cout << boolalpha << "( " << date1 << " <= " << date2  << ") = " << (date1 <= date2) << '\n';
    cout << boolalpha << "( " << date1 << " >  " << date2  << ") = " << (date1 > date2)  << '\n';
    cout << boolalpha << "( " << date1 << " >= " << date2  << ") = " << (date1 >= date2) << '\n';
    cout << boolalpha << "( " << date1 << " == " << date2  << ") = " << (date1 == date2) << '\n';
    cout << boolalpha << "( " << date1 << " != " << date2  << ") = " << (date1 != date2) << '\n';
}

void test_difference_between_dates() {
    Date date1{"03-02-2021"};
    Date date2{"18-05-2023"};

    std::cout << "date1 = " << date1 << " " << "date2 = " << date2 << '\n';

    std::cout << "date1 - date2 = " << date1 - date2 << '\n';
    std::cout << "date2 - date1 = " << date2 - date1 << '\n';

    std::cout << "date1 + (date2-date1) == date2 ---> " << std::boolalpha
              << (date1 + (date2-date1) == date2) << '\n';

    std::cout << "date1 - (date1-date2) == date2 ---> " << std::boolalpha
              << (date1 - (date1-date2) == date2) << '\n';

    std::cout << "date2 + (date1-date2) == date1 ---> " << std::boolalpha
              << (date2 + (date1-date2) == date1) << '\n';
}

void test_weekday() {
    Date::WeekDay wd{Date::WeekDay::Sunday};
    wd++;
    std::cout << "first day of week = " << wd << '\n';

    std::cout << "--wd = " << --wd << '\n';

    std::cout << "++wd = " << ++wd << '\n';

    std::cout << "++wd = " << ++wd << '\n';
}

int main()
{
    std::cout << "**************** Test Increment Decrement ****************\n\n";
    test_operator_increment_decrement();
    std::cout << "\n************** Test Random Date *****************\n\n";
    test_randomDate();
    std::cout << "\n************** Test Compare Date *****************\n\n";
    test_compare_operator();
    std::cout << "\n************** Test Difference Date *****************\n\n";
    test_difference_between_dates();
    std::cout << "\n************** Test Week Day *****************\n\n";
    test_weekday();
}
