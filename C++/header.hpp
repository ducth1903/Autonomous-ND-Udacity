#ifndef HelloWorld_hpp
#define HelloWorld_hpp

// Can store both function declaration and function definition in the header file
void increment(int *input);
void passArrPtr(int *arr, int sizeArr);
int constInput(const int input);

void increment(int *input)
{
    (*input)++;
}

void passArrPtr(int *arr, int sizeArr) {
    
}

// Good practice: define a variable as 'const' if we don't want that variable to be modified in the function
int constInput(const int input) {
    return 0;
}

#endif