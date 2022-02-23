/*******************************************************************************
 * Name        : student.cpp
 * Author      : Michael Bearint
 * Date        : 9/8/2021
 * Description : Student Class
 * Pledge      : I pledge my honor that I have abided by the stevens honor system
 ******************************************************************************/


#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Student {
    private:
    string first_;     
    string last_ ;    
    float gpa_;     
    int id_; 

    public:
    Student(string f, string l, float g, int id) : first_{f}, last_{l}, gpa_{g}, id_{id} { }

    //methods
    string full_name() const {
        return first_ + last_;
    }

    int id() const{
        return id_;
    }

    float gpa() const{
        return gpa_;
    }

    void print_info() const {
		cout << first_ << " " << last_ << ", GPA: " << fixed
			 << setprecision(2) << gpa_ << ", ID: " << id_;
	}
};

/***Takes a vector of Student objects, and returns a new vector* with all Students whose GPA is <1.0.*/
vector<Student>find_failing_students(const vector<Student>&students){
    vector<Student>failing_students;
    //Iterates through the students vector, appending each student whose gpa is
    //less than 1.0 to the failing_students vector.
    for(const auto &student : students) {
		if(student.gpa() < 1.0) {
			failing_students.push_back(student);
		}
	}
    return failing_students;
    }

/***Take a vector of Student objects and prints them to the screen.*/
void print_students(const vector<Student>&students){ 
    //Iterates through the students vector, calling print_info() foreach student.
    for(const auto &student : students) {
		student.print_info();
        cout << endl;
	}

}

/***Allowstheusertoenterinformationformultiplestudents,then*findthosestudentswhoseGPAisbelow1.0andprintsthemtothe*screen.*/
int main(){
    string first_name,last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;
    do{
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while(gpa < 0|| gpa > 4){
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name,last_name,gpa,id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while(repeat=='Y'||repeat=='y');

    cout << endl << "All students:" << endl;
    print_students(students);

    cout << endl << "Failing students:";
    vector<Student> failing = find_failing_students(students);
    if(failing.empty() == true){
        cout << " None";
    }else{
        cout << endl;
        int size = failing.size();
        int count = 1;
        for(const auto &student : failing) {
		student.print_info();
        if(count < size){
            cout << endl;
        }
        count++;
	}
    }


    return 0;
    }