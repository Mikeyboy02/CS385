
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

int main(){
    for (int i = 0; i <=40; i++){
        if((4*i*i*i)>(64*i* log2(i))){
            cout << i << endl;
        }
    }
    return 0;
}