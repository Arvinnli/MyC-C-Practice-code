#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>


using namespace std;

#ifdef __cplusplus
extern "C"{
#endif



int main(int argc,char** argv){
	int i,j,depth=7;
	for(j=0;j<depth;j++){
		int w = 1 << (depth - j + 1);
		if(j==0){
			printf("%*c\n",w,'_');
		}else{
			for(i=0;i<1<<(j-1);i++){
				printf("%*c",w+1,' ');
				for(int k=0;k<w-3;k++){
					cout << "_" ;
				}
				cout << "/ \\";
				for(int k=0;k<w-3;k++){
					cout << "_" ;
				}
				printf("%*c",w+2,' ');
			}
			cout << endl;
			for(i=0;i<1<<(j-1);i++){
				printf("%*c/%*c_%*c",w,'_',w*2-2,'\\',w,' ');
			}
			cout << endl;
		}
		for(i=0;i<1<<j;i++){
			printf("%*c%*c",w,'o',w,' ');
		}
		cout << endl;
	}

    return 0;
}








#ifdef __cplusplus
}
#endif