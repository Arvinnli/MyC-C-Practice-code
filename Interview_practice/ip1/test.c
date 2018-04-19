
int sum(int a,int b){

    return a + b;
}
int max(int a,int b){

    return a>b ? a : b;
}

int main(){

    int a,b,c,d;

    a  = 4 ;
    b  = 5 ;
    c  = 0 ;
    d  = 0 ;

    c = sum(a,b);
    d = max(a,b);



    return c+d;
}

