/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Michael Bearint
 * Date        : 9/23/21
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    int i = 0;
    char c;
    while (s[i]){
      c=s[i];
      if(isupper(c) || isdigit(c)){
          return false;
      }else{
          i++;
      }
   }
   return true;
}

bool all_unique_letters(const string &s) {
    unsigned int vector = 0;
    unsigned int setter;
    char c;
    int i = 0;
    while(s[i]){
        c = s[i];
        setter = 1 << (c - 'a');
        if((vector & setter) !=0){
            return false;
        }else{
            vector = vector | setter;
            i++;
        }
    }
    return true;
    
}

int main(int argc, char * const argv[]) {
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return 0;
    }
    string word = argv[1];
    if(is_all_lowercase(word) == false){
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 0;
    }else{
    if(all_unique_letters(word)==true){
        cout << "All letters are unique." << endl;
    }else{
        cout << "Duplicate letters found."<< endl;
    }
    }
    

}
