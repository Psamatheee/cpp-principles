//
// Created by julia on 16/04/22.
//

#ifndef TEMP_READINGS_TEMPREADING_H
#define TEMP_READINGS_TEMPREADING_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <map>
using namespace std;

    constexpr double not_reading = -777; // less than absolute 0
    constexpr int not_month = -1;
    constexpr int days_num = 32; // 32 days to "waste" day[0] to make reading eaiser

    const map<string, int> month_table = {{"jan", 0}, {"feb",1}, {"mar",2}, {"apr",3},
                                    {"may",4}, {"jun",5}, {"jul",6}, {"aug",7},
                                    {"sep",8}, {"oct",9}, {"nov",10}, {"dec",11}};

    struct Reading{
        int day;
        int hour;
        double temp;
    };

    struct Day{
        vector<double> hour{vector<double>(24,not_reading)};
    };

    struct Month{
        int month{not_month};
        vector<Day> day{days_num};
    };

    struct Year{
        int year;
        vector<Month> month{12};
    };



#endif //TEMP_READINGS_TEMPREADING_H
