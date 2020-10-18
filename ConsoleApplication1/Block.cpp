#ifndef BLOCK
#define BLOCK

class Block {
    private:
        Block* location;
    
    public: 
        Block* getBlockLocation() {
            return this;
        }

        void selfDestructBlock() {
            delete this;
        }

};

#endif