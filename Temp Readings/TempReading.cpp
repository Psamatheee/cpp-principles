//
// Created by julia on 16/04/22.
//

#include "TempReading.h"



void end_of_loop(istream& ist, char term, const string& message)
{
    if (ist.fail()) {
// use term as terminator and/or separator
        ist.clear();
        char ch;
        if (ist>>ch && ch==term) return;
// all is fine
        throw runtime_error(message);
    }
}

bool is_valid(const Reading& r){
    if(r.day<1 || r.day>32) return false;
    if (r.hour < 0 || r.hour >23) return false;
    if (r.temp < -274 || r.temp > 400) return false;
    return true;
}


istream& operator>>(istream& is, Reading& r)
// read a temperature reading from is into r
// format: ( 3 4 9.7 )
// check format, but don’t bother with data validity
{
    char ch1;
    if(is>>ch1 && ch1 != '(' ){ //if the first character is read but isnt the correct format
        is.unget(); //put back the cahracer to try to read info in another way
        is.clear(ios_base::failbit);
        return is;
    }

    char ch2;
    int d;
    int h;
    double t;
    is>>d>>h>>t>>ch2;
    if(!is||ch2 != ')') throw runtime_error("bad reading");
    r.day = d;
    r.hour = h;
    r.temp = t;
    return is;

}

istream& operator>>(istream& is, Month& m)
// read a month from is into m
// format: { month feb  (. . . }
{
    char ch1;
    if(is>>ch1&& ch1!='{'){
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }
    string month_marker;
    string month;
    string mm;
    is >> month_marker >> mm;
    if(!is || month_marker != "month") throw runtime_error("bad start of month");
    m.month = month_table.at(mm);

    int duplicates = 0;
    int invalids = 0;
    for(Reading r; is >> r;){
        if(is_valid(r)){
            if(m.day[r.day].hour[r.hour] != not_reading) {duplicates++;}
            else{
                m.day[r.day].hour[r.hour] = r.temp;
            }
        }else{
            invalids++;
        }

    }

    if(invalids) throw runtime_error(to_string(invalids) + " invalid dates");
    if(duplicates) throw runtime_error(to_string(duplicates) + "duplicate dates");

    end_of_loop(is,'}', "Bad end of month");
    return is;
}

istream& operator>>(istream& is, Year& y){
    char ch1;
    is >> ch1;
    if(ch1!='{'){
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    string year_marker;
    int yy;
    is >> year_marker >> yy;

    if(!is || year_marker!="year"){
        throw runtime_error("bad start of year");
    }

    y.year = yy;
    bool exit = false;
    while(!exit){
        Month m;
        if(!(is>>m)) {exit = true;
        }else{
            y.month[m.month] = m;
        }

    }
    end_of_loop(is,'}',"Bad end of year");
    return is;


}

ostream& operator<<(ostream& os, Day& d){
    for(int i = 0; i < 24; i++){
        if(d.hour[i] != not_reading){
            os << "hour: " << i << " temp: " << d.hour[i] << "\n";
        }
    }
    return os;
}
ostream& operator<<(ostream& os, Month& m){
    if(m.month != not_month){
        Day def_day;
        for(int i =1; i < 32; i++){
            if(m.day[i].hour != def_day.hour){
                os << "DAY " << i << "\n" << m.day[i];
            }
        }
    }

    return os;

}

ostream& operator<<(ostream& os, Year& year){
    os << "YEAR: " << year.year << "\n";
    for(Month& m : year.month){
        if(m.month != not_month){
            os << "MONTH " << m.month+1 << "\n" << m;
        }

    }
    return os;
}

void print_year(ostream& ofs, Year& y){
    cout << y;
    ofs << y;
    cout << "==========================================\n";
    ofs << "==========================================\n";


}
