#include <iostream>
using namespace std;


void display_array(int array[], int length){
    for(int i = 0; i < length; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}

//display with pointers
void display_array_ptr(int *array, int length){
    for(int *p = array; p < array + length ; p++){
        cout << *p << " ";
    }
    cout << endl;
}


//makes a copy
    void pass_by_value(int k){
        k = 10;
    }

//changes variable by using pointer
    void pass_by_pointer(int *k){
        *k = 10;  //same as x = 10
            // same as address of x
    }

   //simpler to write and easier to use
    void pass_by_reference(int &k){
        k = 10;
    }

int main(){
    int x = 5; //type integer

    int *z;  // pointer to integer
    z = &x  // stores the address of x in z
    //can also do it in one line
    //int x = 5, *z = &x;
    //pointer dereference
    //if z == &x then *z is the same as x itself
    *z = 7; // same as x = 7;

    cout << "*z is: " << *z << endl;

    pass_by_pointer(&x);


    //arrays    Need to allocate memory with pointer
    //returns start value of the array
    int *values = new int[x];
    for(int i = 0; i < x; i++) {
        //can use either of these but the second is easier
        *(values + i) = i;
        values[i] = i;
    }
    display_array(values, x);
    display_array_ptr(values, x);
    delete [] values;
 

    return 0;
}