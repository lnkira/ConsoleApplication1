#include "Record.cpp"
#include "Block.cpp"
#include "vector"
#include <string>
#include <iostream>

class DataBlock {
    private:
        char header[10];
        int MAXNOOFRECORDS = 5;
        vector<Record> records;
    
    public: 
        bool isFull(){
            return this->records.size() == MAXNOOFRECORDS? true : false;
        }

        bool isEmpty() {
            return this->records.empty()? true : false;
        }

        Record* getRecordLocs() {
            return this->records.data();
        }
        
        int getNoOfRecords() {
            return this->records.size();
        }
        
        void printRecordsInBlock(){
            for (Record r : records){
                cout << r.getTconst() << endl;
            }
        }

        void addRecord(Record inputRecord){ 
            this->records.push_back(inputRecord);
            // if (this->isFull()) return false;

            // else { //this else statement needs to allow adding of records in sequence of their average votes 
            //     Record* latestRecordAddress = &(this->records[this->emptyIndexNo]); //get address of the first empty slot in records
            //     float inputKey = inputRecord.getAverageRating();
            //     int indexOfInput;
            //     int indexOfLastRecord = emptyIndexNo - 1;

            //     for (int index = 0; index < emptyIndexNo; index++) {
            //         float oldKey = records[index].getAverageRating();
            //         if (inputKey < oldKey) indexOfInput = index;
            //     }

            //     if (indexOfInput == emptyIndexNo) records[emptyIndexNo] = inputRecord; //means new record is to be inserted at the back of the array of records
            
            //     else {
            //         for (;indexOfLastRecord >= indexOfInput;) { //this loop shifts the old records backwards to allow new record to be inserted in the correct location
            //             records[emptyIndexNo] = records[indexOfLastRecord];
            //             emptyIndexNo -= 1;
            //             indexOfLastRecord -= 1;
            //         }

            //         records[emptyIndexNo] = inputRecord;
            //     }

            //     this->setEmpty(emptyIndexNo + 1); //update the empty index

            //     return true;
            // }
        }

        void getRecordDatafromRecordPtr(Record* recordPtr) { //might not be needed
            // std::string tconst = recordPtr->getTconst();
            // float averageRatings = recordPtr->getAverageRating();
            // int numVotes = recordPtr->getNumVotes();
            // Record record = Record(tconst, averageRatings, numVotes);

            // return record;
        }

        void deleteRecord(Record* inputRecordAddress) {
            // this->records.erase(remove(this->records.begin(), this->records.end(), inputRecordAddress), this->records.end());
            // int toDelete;
            // int next;
            // int lastFilledIndex = emptyIndexNo -1;

            // for (int index = 0; index < MAXNOOFRECORDS; index++) {
            //     if (&(records[index]) == inputRecordAddress) { //find the record with the specified address
            //         toDelete = index;
            //         next = toDelete + 1;

            //         for (;next <= lastFilledIndex;) { //shift the remaining records forward
            //             records[toDelete] = records[next];
            //             toDelete = next;
            //             next += 1;
            //         }

            //         this->setEmpty(emptyIndexNo -1); //update the empty index number of records

            //         if (emptyIndexNo == 0) this->selfDestructBlock();

            //         return true;
            //     } 
            // } 

            // return false; //if we get to this part of the code, means this DataBlock does not have a record with the specified address 

        }

        void getSmallestKey() {
            // int smallestKey = 10;
            // for (int i = 0; i < MAXNOOFRECORDS; i++) {
            //     if (records[i].getAverageRating() < smallestKey) {
            //         smallestKey = records[i].getAverageRating();
            //     }
            // }

            // return smallestKey;
        }


        
};