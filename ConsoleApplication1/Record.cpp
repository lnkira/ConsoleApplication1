#ifndef RECORD  
#define RECORD

#include <string>

using namespace std;

class Record {
    private:
        string TCONST;
        float AVERAGERATING;
        int NUMVOTES;
    
    public: 
        Record (string tconst, float avg, int votes) {
            this->TCONST = tconst;
            this->AVERAGERATING = avg;
            this->NUMVOTES = votes;
        }

        string getTconst() {
            return TCONST;
        }

        float getAverageRating() {
            return AVERAGERATING;
        }

        int getNumVotes() {
            return NUMVOTES;
        }

        void selfDestructRecord() {
            delete this;
        }

};

#endif