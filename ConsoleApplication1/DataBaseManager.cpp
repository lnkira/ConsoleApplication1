#include "DataBlock.cpp"
#include <iostream>
#include <string>
#include "vector" 
#include "algorithm"
#include <math.h>

using namespace std;

class DataBaseManager {
    private:
        vector<DataBlock> blocks;
    
    public:
        void addRecord(Record record) {
            if (blocks.empty()|| blocks.back().isFull()) {
                DataBlock newBlock = DataBlock();
                blocks.push_back(newBlock);
            }

            blocks.back().addRecord(record);
        }

        DataBlock* getBlockLocations() {
            return blocks.data();
        }

        int getNoOfBlocks() {
            return blocks.size();
        }

};