/*
Hello World program
- To compile: g++ helloworld.cpp -o helloworld.out
- To run: ./helloworld.out
*/
#include <iostream>

using namespace std;

int main() {
    cout << "Hello World" << endl;

    int myInt = 1234;
    cout << "The value is " << myInt << endl;

    // Enumerate constants (create a new variable type and assign a finite number of values to it)
    enum MONTH {Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};
    MONTH myMonth = Mar;
    cout << "My month is " << myMonth << endl;
    
    return 0;
}