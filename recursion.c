#include <iostream>

using std::cin;
using std::cout;
using std::endl;


int fib2_0(int n, int pp=0, int pre=1, int p=2) {
    if(n<=0) return n;
    if(n==p){ 
        int rez = pp + pre;
        return rez;

    }
    return fib2_0(n, pre, pre+pp, p+1);
    
}

int nzd(int x, int y){
    if(y==0) return x;
    return nzd(y, x%y);
}

int main() {
    
    return 0;
}
