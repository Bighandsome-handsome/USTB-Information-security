#include "Stack.h"
#include <iostream>
#include <math.h>
using namespace std;
Stack::Stack() {
    top = -1;
}
// push(x) is used to store the value of result in the Array arr[].
void Stack::push(double x) {
    top++;
    arr[top] = x;
}
void Stack::pop() {
    if (top == -1) {
        return;
    }
    top--;
}
// Top() is used to output the value stored in Array arr[].
double Stack::Top() {
    if (top == -1) {
        cout << "No result value stored" << endl;
        return -1;
    }
    return arr[top];
}
