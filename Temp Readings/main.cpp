#include <iostream>
#include "TempReading.cpp"
#include <fstream>

int main() {
    cout<<"Enter input file name: ";
    string ifile;
    cin >> ifile;
    ifstream ist{ifile};
    if(!ist) throw runtime_error("No file");

    ist.exceptions(ist.exceptions()|ios_base::badbit);

    cout << "Enter output file name: ";
    string ofile;
    cin >>ofile;
    ofstream ost{ofile};
    if(!ost) throw runtime_error("No file");

    vector<Year> years;
    bool exit = false;
    while(!exit){
        Year y;
        if(ist >> y){


            years.push_back(y);
        }else{
            exit = true;
        }
    }

    for(Year y : years){
        print_year(ost, y);
    }
    return 0;
}
