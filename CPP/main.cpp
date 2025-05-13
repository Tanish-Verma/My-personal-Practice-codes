#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* arr;  // Pointer to the dynamic array
    int size;

public:
    // Constructor: Allocates memory for the array
    DynamicArray(int s) {
        size = s;
        arr = new int[size];  // Allocating memory dynamically
        cout << "Constructor: Dynamic array of size " << size << " created." << endl;
    }

    // Destructor: Frees the allocated memory
    ~DynamicArray() {
        delete[] arr;  // Free the allocated memory
        cout << "Destructor: Dynamic array memory released." << endl;
    }

    // Function to set values in the array
    void setValue(int index, int value) {
        if (index >= 0 && index < size) {
            arr[index] = value;
        }
    }

    // Function to display values in the array
    void display() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // Create an object of DynamicArray with size 5
    DynamicArray da(5);

    // Set values in the array
    da.setValue(0, 10);
    da.setValue(1, 20);
    da.setValue(2, 30);
    da.setValue(3, 40);
    da.setValue(4, 50);

    // Display the array
    da.display();

    // When the function ends, the destructor will automatically be called
    return 0;
}
