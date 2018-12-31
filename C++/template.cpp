// Templates --- Generic programming
#include <iostream>

using namespace std;

// Generic function
template <typename T>
T sumTwo(T a, T b)
{
    T sum = a + b;
    return sum;
}

template <typename T, typename U>
T getBigger(T input1, U input2)
{
    if (input1 > input2)
        return input1;
    else
        return input2;
}

// Generic class
// Everywhere we see T, this is where we would substitute int, char, float or string
// And the member functions must all be treated as generic functions => have to add the template command to each member function,
// even for the function that you don't use generic
template <class T>
class StudentRecord
{
    private:
    const int size = 5;
    T grade;
    int studentId;

    public:
    StudentRecord(T input);
    void setId(int newId);
};

template <class T>
StudentRecord<T>::StudentRecord(T input)
{
    grade = input;
}
// even though it is not a generic function, it is in a generic class!
template <class T>
void StudentRecord<T>::setId(int newId)
{
    studentId = newId;
}

// MAIN
int main()
{
    int a = 10;
    int b = 9;
    cout << "Sum is " << sumTwo(a,b) << endl;

    float c = 2.0;
    int d = 6;
    cout << "Bigger is " << getBigger(c,d) << endl;

    StudentRecord<int> srInt(3);
    srInt.setId(123);
    
    StudentRecord<float> srFloat(3.333);
    srFloat.setId(321);

    return 0;
}