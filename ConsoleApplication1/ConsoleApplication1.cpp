#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "vector"

using namespace std;


int main()
{
    string tconst;
    string avg;
    string vote;
    ifstream fileIn("./data2.tsv");

    if(!fileIn.is_open())
         cout << "file failed to open" << endl;

    std::istringstream lin;
    for (std::string line; std::getline(fileIn, line); ) {
        lin.clear();
        lin.str(line);
        if (lin >> tconst >> avg >> vote)
            cout << tconst << " " << avg << " " << vote << endl;
        //getline(fileIn, tconst, ',');
        //getline(fileIn, avg, ',');
        //getline(fileIn, vote, '\n');
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
