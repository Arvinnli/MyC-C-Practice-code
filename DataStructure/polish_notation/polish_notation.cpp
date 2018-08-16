#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>


using namespace std;

#ifdef __cplusplus
extern "C"{
#endif

#ifdef TRACE_INFO_SUPPORT
#define sci_trace_low(...) printf(__VA_ARGS__)
#else
#define sci_trace_low(...) 

#endif
typedef enum{NUM,ADD,SUB,MUL,DIV}TYPE_E;
typedef struct NodeTag{
	union{
		double number;
		struct NodeTag* children[2];
	}u;
	TYPE_E type;
}Node;
typedef struct{
	int len;
	Node buf[0];
}Nodebuf;


void release(Node* node);
Node* parse(char* str);
void printInfix(const Node* node);
double eval(const Node* node);


int main(int argc,char** argv){

	if(argc!=2){
		return printf("help: pntree \" + * 1 2 3 \"\n");
	}else{
		char* p = argv[1];
		Node* root = parse(p);
		if(root){
			printInfix(root);
			printf(" = %lg\n",eval(root));
			release(root);
		}else{
			return printf("Invalid input\n");
		}
	}
	// char* str = "abc345xxx";
	// char* ptr = NULL;
	// double d = strtod(&str[3],&ptr);
	// printf("%f\n",d);
	return 0;
}



Node* parse(char* str){
	int i;
	char* ptr = NULL;
			// sci_trace_low("str:%s\n",str);
	
	for(i=0;isspace(str[i]);i++);
	if(str[i]==0){
		return NULL;
	}else{
		Node* node = (Node*)malloc(sizeof(Node));
		if(isdigit(str[i])){
			node->type = NUM;
			node->u.number = strtod(&str[i],&ptr);

		}else{			
			switch(str[i]){
				case '+':node->type = ADD;break;
				case '-':node->type = SUB;break;
				case '*':node->type = MUL;break;
				case '/':node->type = DIV;break;
				default:release(node);return NULL;
			}
			i++;
		
			// i++;
			for(int j=0;j<2;j++){
				sci_trace_low("str[i]:%s\n",&str[i]);
				if((node->u.children[j]=parse(&str[i]))==NULL){
					release(node);
					sci_trace_low("line:%d\n",__LINE__);
					return NULL;
				}
			}
		}
		return node;
	}
}



void release(Node* node){
	int i;
	if(node->type!=NUM){
		for(i=0;i<2;i++){
			if(node->u.children[i]){
				release(node->u.children[i]);
			}
		}
	}
	free(node);
}

#define OPERATOR_CHAR(n) ("+-*/"[n->type-ADD])

void printInfix(const Node* node){
	if(node->type==NUM){
		printf("%lg",node->u.number);
	}else{
		putchar('(');
		printInfix(node->u.children[0]);
		printf(" %c ",OPERATOR_CHAR(node));
		printInfix(node->u.children[1]);
		putchar(')');
	}
}

double eval(const Node* node){
	switch(node->type){
		case ADD:return eval(node->u.children[0]) + eval(node->u.children[1]);
		case SUB:return eval(node->u.children[0]) - eval(node->u.children[1]);
		case MUL:return eval(node->u.children[0]) * eval(node->u.children[1]);
		case DIV:return eval(node->u.children[0]) / eval(node->u.children[1]);
		case NUM:return node->u.number;
	}
}










#ifdef __cplusplus
}
#endif