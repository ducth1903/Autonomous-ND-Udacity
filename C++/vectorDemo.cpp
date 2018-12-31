/*
- Vectors are more versatile than arrays and can be resized during runtime
- Use iterator to cycle through the vector
- ::assign overwrites the elements in the vector
- ::push_back adds elements to the end of a vector
- ::insert adds elements to the location via the iterator -> need to set the iterator to the desired location
- ::emplace puts an element in a vector at the position pointed to by the iterator
    (insert copies the values of the vector while emplace does an in-place insertion)
- ::clear removes all elements from a vector at the same time
- ::erase removes specific elements from a vector (can delete a single element or a range of elements)
- ::pop_back removes the last element of a vector (DOES NOT return value)
*/

#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int> vec);

int main()
{
    // Create a vector of integers
    vector<int> vectorInts;
    cout << "vectorInts has " << vectorInts.size() << " elements" << endl;

    // Change the size of vectorInts to 6
    vectorInts.resize(6);
    cout << "vectorInts has " << vectorInts.size() << " elements" << endl;
    printVector(vectorInts);

    // Assign value 3 to the 4 elements of the vector (the remaining 2 elements are ignored)
    vectorInts.assign(4,3);
    printVector(vectorInts);

    // Add elements to the end of the vector
    vectorInts.push_back(1);
    vectorInts.push_back(2);
    printVector(vectorInts);

    // add -1 as the second element of the vector
    vector<int>::iterator it = vectorInts.begin();
    vectorInts.insert(it + 1, -1);
    printVector(vectorInts);

    return 0;
}

void printVector(vector<int> vec)
{
    // Use iterator to cycle through the vector
    vector<int>::iterator it;
    for (it = vec.begin(); it != vec.end(); ++it)
        cout << *it << " ";
    cout << endl;
}