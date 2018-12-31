#include <iostream>
#include <string>

using namespace std;

// By default, all attributes are private!
// (->) is used for accessing POINTER members of a class
class Student
{
    int id;
    string name;
    int gradDate;

    // Functions that access and/or modify data in class are called mutators
    public:
    Student();      // declaring the constructor (constructor does not return value, including void)
    Student(int newid, string newname, int newgradDate);
    void setName(string newName);
    void setId(int newId);
    void setGradDate(int newDate);
    string getName();
    int getId();
    int getGradDate();
    void printStudent();
    ~Student();     // deconstructor

    int operator - (Student st2)
    {
        return getGradDate() - st2.getGradDate();
    }
};

Student::Student()
{
    name = "Unknown";
    id = 0;
    gradDate = 0;
}

// Overloading constructor
Student::Student(int newid, string newname, int newgradDate)
{
    id = newid;
    name = newname;
    gradDate = newgradDate;
}

Student::~Student()
{
    cout << "Deleting student name " << name << endl;
}

void Student::setName(string newName)
{
    name = newName;
}

void Student::setId(int newId)
{
    id = newId;
}

void Student::setGradDate(int newDate)
{
    gradDate = newDate;
}

string Student::getName()
{
    return name;
}

int Student::getId()
{
    return id;
}

int Student::getGradDate()
{
    return gradDate;
}

void Student::printStudent()
{
    cout << name << " " << id << " " << gradDate << endl;
}

// -------------------------- Class Inheritance --------------------------
// The derived class from parent/base class Student
// 3 types of access control: public, private, protected...
// - public inheritance: all public members of the parent class are accessible to the derived class
// - private inheritance: all members of the parent class are private to the derived class
// - protected inheritance: all members of the parent class are protected to the derived class
class GradStudent : public Student
{
    string degree;

    public:
    GradStudent();
    void setDegree(string degreeIn);
    string getDegree();
};

GradStudent::GradStudent()
{
    degree = "undeclared";
}

void GradStudent::setDegree(string degreeIn)
{
    degree = degreeIn;
}

string GradStudent::getDegree()
{
    return degree;
}

// -------------------------- Multiple Inheritance --------------------------
// Inherits attributes from multiple parent classes
// i.e. class TA: public Staff, public GradStudent
// Class TA inherits from both class Staff and class GradStudent

// -------------------------- Polymorphism (many forms) --------------------------
// In C++, we use virtual function to allow functions to be dynamic bounded during execution
// A virtual function is a member function that you expect to be redefined in derived classes
// When you refer to a derived class object using a pointer or a reference to the parent class, you can call a virtual function for that object
// and execute the derived class's version of the function

// => only add keyword 'virtual' in one location in the parent/base class === similar to ABSTRACT in Java

// -------------------------- Main program --------------------------
int main()
{
    Student student1;
    student1.setName("Duc Tran");
    student1.setId(123);
    student1.setGradDate(111);
    student1.printStudent();

    Student student2(1,"AB",100);
    int diff = student1 - student2;
    cout << "Student 1: " << student1.getGradDate() << "\t" << "Student 2: " << student2.getGradDate() << endl;
    cout << "Difference in grad date = " << diff << endl;

    cout << "------------------------" << endl;
    return 0;
}