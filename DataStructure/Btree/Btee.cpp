#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>


using namespace std;


class BtreeNode{
	public:
		Btree(){
			this->mRight = NULL;
			this->mLeft = NULL;
		}
		Btree(int data){
			this->mData = data;
		}

		void setData(int data){
			this->mData = data;
		}
		int getData(void){
			return this->mData;
		}
		void setLeft(BtreeNode* left){
			this->mLeft = left;
		}
		BtreeNode* getLeft(void){
			return this->mLeft;
		}
		void setRight(BtreeNode* right){
			this->mRight = right;
		}
		BtreeNode* getRight(void){
			return this->mRight;
		}
        
	private:
		BtreeNode* mLeft;
		BtreeNode* mRight;
		int mData;
	protected:
};	




int main(int argc,char** argv){


    return 0;
}