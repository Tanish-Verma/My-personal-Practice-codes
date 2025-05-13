import sys
import math

# Tolerance for approximate comparison
EPSILON = 1e-5

# Function to compare two floating-point numbers approximately
def are_approximately_equal(a, b):
    return abs(a - b) < EPSILON

def main():
    # Get n from command-line argument
    if len(sys.argv) < 2:
        print("Usage: python compare_solutions.py <n>")
        return
    
    n = int(sys.argv[1])  # Size of the vector
    
    x_computed = []
    # Read computed values from computed_values.txt
    try:
        with open("computed_values.txt", "r") as file:
            for line in file:
                x_computed.append(float(line.strip()))
    except FileNotFoundError:
        print("Could not open computed_values.txt")
        return
    except ValueError as e:
        print(f"Error reading computed values: {e}")
        return

    if len(x_computed) != n:
        print(f"Error: Expected {n} computed values, but got {len(x_computed)}.")
        return
    
    x_from_file = []

    # Read solution vector from solutions.txt
    try:
        with open("solutions.txt", "r") as file:
            for line in file:
                x_from_file.append(float(line.strip()))
    except FileNotFoundError:
        print("Could not open solutions.txt")
        return
    except ValueError as e:
        print(f"Error reading solution values: {e}")
        return

    if len(x_from_file) != n:
        print(f"Error: Expected {n} values in solutions.txt, but got {len(x_from_file)}.")
        return

    # Compare each element of the computed x with the corresponding value from solutions.txt
    mismatch_found = False  # Flag to track if any mismatch occurs
    for i in range(n):
        if not are_approximately_equal(x_computed[i], x_from_file[i]):
            print(f"Mismatch at index {i}: Computed = {x_computed[i]}, Expected = {x_from_file[i]}")
            mismatch_found = True
    
    # Final statement based on whether there were mismatches
    if mismatch_found:
        print("Comparison complete. Mismatches found.")
    else:
        print("Comparison complete. All computed values match with original values.")

if __name__ == "__main__":
    main()
