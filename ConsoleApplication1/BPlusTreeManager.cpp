#include "vector" 
#include "algorithm"
#include <math.h>
#include "DataBaseManager.cpp"
#include "BpNode.cpp"

using namespace std;

class BPlusTreeManager {
    private:
        int indexOfRoot;
        int height;
        int order;
        BpNode* rootNode;

    public: 
        BPlusTreeManager(int n) {
            height = 0;
            order = n;
            rootNode = new BpNode(order);
        }

        void buildTree(DataBlock* blocks, int noOfBlocks) {

            for (int i = 0; i < noOfBlocks; i++) {
                Record* rptr = blocks[i].getRecordLocs();
                for (int j = 0; j < blocks[i].getNoOfRecords(); j++) {
                    this->insert(rootNode, &rptr[j]);
                    getAllKey();
                    cout << endl;
                }
            }
        }

        int insert (BpNode* nodePtr, Record* key) { //insert key into leaf node
            if (nodePtr->getIsLeaf() == true) { //this node is a leaf node
                //insert into this leaf node
                cout << "Inserting key " << key->getAverageRating() << endl;
                if (nodePtr->insert(key, order) == 0) {//node is splitted
                    //insert pointer to new leaf node to parent
                    if (this->rootNode == nodePtr) { //root node is splitted
                        BpNode* newNode = new BpNode(order); //create new node
                        newNode->insert(nodePtr, order); //link new node to splitted nodes
                        newNode->setLeaf(false);
                        this->rootNode = newNode; //set new node as root node
                        return 1;
                    }
                    return 0;
                }
                return 1;
            }
            else { //this node is not a leaf node
                //search for children node to insert into
                BpNode* childPtr; //node to be inserted to
                float* keys = nodePtr->getKeys(); //get keys of current node to compare with
                int i = 0;
                for (i = 0; i < nodePtr->getNoOfKey(); i++) {
                    if (key->getAverageRating() < keys[i]) //found index of children node
                        break;
                }
                childPtr = nodePtr->getChildPtr(i);
                if (insert(childPtr, key) == 0) { //leaf node overflow
                    //insert pointer to existing non-leaf node
                    if (nodePtr->insert(childPtr, order) == 0) { //non-leaf node overflow
                        if (this->rootNode == nodePtr) { //root node is splitted
                            BpNode* newNode = new BpNode(order); //create new node
                            newNode->insert(nodePtr, order);
                            nodePtr->setChildrenNode(NULL, order);//unlink both non-leaf nodes
                            newNode->setLeaf(false);
                            this->rootNode = newNode; //set new node as root node
                            return 1;
                        }
                        return 0;
                    }
                }
            }
        }

        int deleteRecord(BpNode* nodePtr, float key) {
            if (nodePtr ->getIsLeaf() == true)
                nodePtr->deleteKey(key);
            else { //search for leaf node
                int i;
                float* keys = nodePtr->getKeys();
                for (i = 0; i < nodePtr->getNoOfKey(); i++) {
                    if (key < keys[i]) //found index of children node
                        break;
                }
                this->deleteRecord(nodePtr->getChildPtr(i), key);
            }
        }
        int deleteRecord(float key) {
            this->deleteRecord(this->rootNode, key);
        }

        void getAllKey() {
            this->getAllKey(rootNode);
        }
        void getAllKey(BpNode* nodePtr) {
            if (nodePtr->getIsLeaf() == true) {
               float* keyptr = nodePtr->getKeys();
               cout << "Leaf node: ";
               for (int i = 0; i < nodePtr->getNoOfKey(); i++)
                   cout << keyptr[i] << " | ";
               cout << endl;
            }
            else {
                int i = 0;
                while (i < nodePtr->getNoOfKey()) {
                    BpNode* node = nodePtr->getChildPtr(i);
                    float* keys = nodePtr->getKeys();
                    cout << node << " " << keys[i] <<" ";
                    i++;
                }
                cout << nodePtr->getChildPtr(i) << endl;

                for (int j = 0; j <= i; j++) {
                    getAllKey(nodePtr->getChildPtr(j));
                }
            }
        }

        void searchRating(float a, float b) {

        }
        
};