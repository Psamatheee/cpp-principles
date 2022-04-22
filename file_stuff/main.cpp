#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

int main() {
    cout << "File name: ";
    string input;
    cin >> input;
    ifstream ist {input};
    if (!ist) {
        cout << "can't find file!\n";
    }else{
        cout << input << " file opened!\n";
    }
    vector<int> nums;
    for(int i; ist >> i;){  // its the same thing as cin but instead of user input being the input, the file is.
        cout << i << "\n";
        nums.push_back(i);
    }

    cout << "Enter name of output file: ";
    string ofile;
    cin >> ofile;
    ofstream ost {ofile};

    if(!ost){
        cout << "Can't find file!\n";
    }else{
        cout << "File found!\n";
    }

    int x;
    while(cin >> x){
        ost << x << "\n";
    }

    return 0;
}
