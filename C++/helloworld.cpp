/*
Hello World program
- To compile: g++ helloworld.cpp -o helloworld.out
- To run: ./helloworld.out
*/

// Logcal Operators: &&, ||, !

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    cout << "Hello World" << endl;

    int myInt = 1234;
    cout << "The value is " << myInt << endl;

    // Enumerate constants (create a new variable type and assign a finite number of values to it)
    enum MONTH {Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};
    MONTH myMonth = Mar;
    cout << "My month is " << myMonth << endl;
    
    /*
    FILE IO:
    - Include <fstream>
    - Create a stream (input, output, both)
        - ofstream myfile; (writing to a file)      => i.e. ofstream myfile ("input.txt", ios::app);
        - ifstream myfile; (for reading a file)     => i.e. ifstream myfile ("input.txt");  then while(getline(myfile, line)) {cout<< line <<endl;}
        - fstream myfile; (for reading and writing a file)
    - Open the file myfile.open("filename");
    - Write or read the file
    - Close the file with myfile.close();
    */

   /*
   cin doesn't retrieve strings with space in between
   => use getline(): getline(cin, userName);
   */
    string stringLength;
    float inches = 0;
    cout << "Enter number: ";
    getline(cin, stringLength);
    stringstream(stringLength) >> inches;   // convert input string to float
    cout << "Entered: " << inches << endl;

    return 0;
}