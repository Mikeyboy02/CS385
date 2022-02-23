/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Michael Bearint
 * Date        : 10/2/2021
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      :I pledge my honor that I have abided by the stevens honor code
 ********************************* * ****************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

//for use in get_ways method
vector <vector <int>> allWays;
vector <int> oneWay;

vector< vector<int> > get_ways(int num_stairs) {

    if(num_stairs != 0){
    //one first so order is the same as the test cases
        if(num_stairs >= 1){
            oneWay.push_back(1);
            get_ways(num_stairs - 1);
            //pop_back clears helps clear the vector when the recursion is done
            //used instead of clear, found pop_back() on page about vector methods
            oneWay.pop_back();
        }
        if(num_stairs >= 2){
            oneWay.push_back(2);
            get_ways(num_stairs - 2);
            oneWay.pop_back();
        }
        if(num_stairs >= 3){
            oneWay.push_back(3);
            get_ways(num_stairs - 3);
            oneWay.pop_back();
        }

    }else{
        //add oneWay vector to allWays if there are no stairs left
        allWays.push_back(oneWay);
        //oneWay.clear();   Didnt work
    }
    
    //return vector of vector containing all the ways you can return
    return allWays;

}

void display_ways(const vector< vector<int> > &ways) {
    
    int maxWidth = 0;
    //sets right alignment for the number of row
    for(size_t i = ways.size(); i>0; i=i/10){
        maxWidth++;
    }
    for (size_t i = 0; i < ways.size(); i++) {

        cout << setw(maxWidth) << (i+1) << ". [";

        //second for loop lists inner vectors
        for (size_t j = 0; j < ways[i].size(); j++){
            if( j+1 == ways[i].size()){
                cout << ways[i][j] << "]";
            }else{
            cout << ways[i][j] << ", ";
            }
        }
        cout << endl;
    }
}

int main(int argc, char * const argv[]) {
    istringstream iss;
    int stairs;

    //all error statements
    if(argc != 2){
        cerr << "Usage: "<<argv[0] << " <number of stairs>" << endl;
        return 1;
    }else{
    iss.str(argv[1]);
    if(!(iss >> stairs)){
        cerr << "Error: Number of stairs must be a positive integer."<< endl;
        return 1;
    }
    if(stairs <= 0){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    //declare vector
    vector < vector<int>> ways = get_ways(stairs);
    if(stairs == 1){
        cout << "1 way to climb 1 stair." << endl;
    }else{
    cout << ways.size() << " ways to climb " << argv[1] << " stairs." << endl;
    }
    display_ways(ways);
    //deletes objects in ways.
    ways.clear();
}
    
}
