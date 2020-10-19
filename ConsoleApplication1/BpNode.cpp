#ifndef BPNODE
#define BPNODE

#include <vector>
#include <iostream>
#include "Record.cpp"

class BpNode {
	
	private:
		vector<float> keys;
		vector<Record*> recordPointer;
		BpNode **children;
		bool isLeaf;

	public:
		BpNode(int n) {
			children = new BpNode* [n+1];
			for (int i = 0; i <= n; i++)
				children[i] = NULL;
			isLeaf = true;
		}
		BpNode() {
			children = NULL;
		}

		int insert(BpNode* leaf, int order) { //insert pointer of leaf node to non-leaf node
			//search for place to insert key
			BpNode* rightPtr = leaf->getChildPtr(order);
			float keyToSearch = rightPtr->keys[0];
			if(rightPtr->getIsLeaf() == true)
				keyToSearch = rightPtr->keys[0];
			else {
				BpNode* searchPtr = rightPtr;
				while (searchPtr->getIsLeaf() != true)
					searchPtr = searchPtr->getChildPtr(0);
				keyToSearch = searchPtr->keys[0];
			}

			int i;
			for (i = 0; i < this->keys.size(); i++) { //search for position to insert key
				if (keyToSearch < this->keys[i]) //found index to insert key
					break;
			}
			if (i != this->keys.size())
				this->keys.emplace(this->keys.begin() + i, keyToSearch); //insert key in the middle
			else
				this->keys.push_back(keyToSearch); //insert key at the end
			if (this->keys.size() <= order) { //check if non-leaf node overflow
				int j = order;
				for (j = order; j > i; j--) { //shifting all the original pointers to the right for inserting new pointers
				if (children[j - 1] != NULL)
					children[j] = children[j - 1];
				}
				children[i] = leaf; //insert left pointer
				children[i + 1] = rightPtr; //insert right pointer
			}
			else { // non-leaf node overflow
				BpNode* newNode = new BpNode(order); //create new non-leaf node
				newNode->setLeaf(false);
				for (int j = ceil((float)order / 2) + 1; j <= order; j++) //split keys
					newNode->keys.push_back(this->keys[j]); //move 2nd half of keys to new node
				while (this->keys.size() > ceil((float)(order) / 2))
					this->keys.pop_back(); //remove keys from current node
				int j;
				if (i < order / 2) { //new pointer is inserted in the original node
					for (j = 0; j <= ceil((float)(order - 1) / 2); j++) {//shift 2nd half of pointers to new node
						newNode->setChildrenNode(this->children[(int)ceil((float)order / 2) + j], j); //shift 2nd half of pointers to new node
						this->children[(int)ceil((float)order / 2) + j] = NULL; //deleting pointers in original node
					}
					for (j = ceil((float)order / 2) + 1; j > i; j--) { //shifting all the original pointers to the right for inserting new pointers
						if (children[j - 1] != NULL)
							children[j] = children[j - 1];
					}
					children[i] = leaf; //insert left pointer
					children[i + 1] = rightPtr; //insert right pointer
				}
				else { //new pointer is inserted in the new node
					BpNode* temp = rightPtr;
					if (i < order) {
						temp = this->children[order];
						for (j = order; j > i; j--) { //shifting all the original pointers to the right for inserting new pointers
							if (children[j - 1] != NULL)
								children[j] = children[j - 1];
						}
						children[i] = leaf; //insert left pointer
						children[i + 1] = rightPtr; //insert right pointer
					}
					for (j = 0; j < order / 2; j++) {//shift 2nd half of pointers to new node
						newNode->setChildrenNode(this->children[(int)ceil((float)order / 2) + j + 1], j); //shift 2nd half of pointers to new node
						this->children[(int)ceil((float)order / 2) + j + 1] = NULL; //deleting pointers in original node
					}
					newNode->setChildrenNode(temp, order / 2);
				}
				children[order] = newNode;//last child pointer points to the new non-leaf node for adding to parent node later
				return 0;
			}
			return 1;
		}

		int insert(Record* key, int order) { //insert into leaf node

			//search for place to insert key
			int i;
			for (i = 0; i < keys.size(); i++) {
				if (key->getAverageRating() <= keys[i])
					break;
			}
			if (i != keys.size()) {
				keys.emplace(keys.begin() + i, key->getAverageRating());
				recordPointer.emplace(recordPointer.begin() + i, key);
			}
			else {
				keys.push_back(key->getAverageRating());
				recordPointer.push_back(key);
			}

			if (keys.size() > order) { //need to split node
				BpNode* newNode = new BpNode(order); //create new leaf node
				newNode->setChildrenNode(this->getChildPtr(order), order); //link new leaf node to current next leaf node
				this->setChildrenNode(newNode, order); //link current leaf node to new leaf node

				for (int i = 1; i <= ceil((float)order / 2); i++)
					newNode->insert(recordPointer[(order / 2) + i], order); //transfer keys to new node
				while (keys.size() > (order / 2)+1) { 
					keys.pop_back(); //remove keys from current node
					recordPointer.pop_back(); //remove pointers from current node
				}
				return 0;
			}
			return 1;
		}

		Record* deleteKey(float key) { //delete key from leaf node
			int i;
			Record* deletedRecord;
			for (i = 0; i < keys.size(); i++) { // search for key to delete
				if (key == keys[i]) {//found key
					deletedRecord = recordPointer[i];
					keys.erase(keys.begin() + i);
					recordPointer.erase(recordPointer.begin() + i);
					return deletedRecord; // successfully deleted
					break;
				}
			}
		}

		BpNode* getChildPtr(int i) {
			return children[i];
		}
		bool getIsLeaf() {
			return this->isLeaf;
		}
		Record** getkeyLocs() {
			return recordPointer.data();
		}
		float* getKeys() {
			return keys.data();
		}
		int getNoOfKey() {
			return this->keys.size();
		}
		void setChildrenNode(BpNode* nodePtr, int index) {
			children[index] = nodePtr;
		}
		void setLeaf(bool isLeaf) {
			this->isLeaf = isLeaf;
		}
		
};

#endif