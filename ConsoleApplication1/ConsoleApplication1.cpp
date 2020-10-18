#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BPlusTreeManager.cpp"

using namespace std;

const int BLOCKSIZE = 100;
const int RECORDSIZE = 17;
const int LEAFNODEKPPSIZE = 8;
const int LEAFNODEPOINTERSIZE = 4;
const int NODEPOINTERSIZE = 4;
const int FLOATPOINTERSIZE = 4;
const int N = 4;

void Experiment1() {
    return;
}

void Experiment2() {
    return;
}

void Experiment3() {
    return;
}

void Experiment4() {
    return;
}

void Experiment5() {
    return;
}

int main()
{
    DataBaseManager dbm = DataBaseManager();
    ifstream fileIn("./data2.tsv");
    string tconst;
    float avg;
    int vote;

    if(!fileIn.is_open())
         cout << "file failed to open" << endl;

    std::istringstream lin;
    for (std::string line; std::getline(fileIn, line); ) {
        lin.clear();
        lin.str(line);
        if (lin >> tconst >> avg >> vote)
        {
            Record newRecord = Record(tconst, avg, vote);
            dbm.addRecord(newRecord);
        }
    }

    fileIn.close();

    BPlusTreeManager dpt = BPlusTreeManager(N);
    float key;
    dpt.buildTree(dbm.getBlockLocations(), dbm.getNoOfBlocks());

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
