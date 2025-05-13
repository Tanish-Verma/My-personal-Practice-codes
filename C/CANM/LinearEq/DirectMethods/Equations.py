import numpy as np
import sys

def generate_equations(n):
    try:
        # Generate a random n x n coefficient matrix
        A = np.random.randint(-2000, 2000, size=(n, n))
        
        # Generate a random solution vector
        x = np.random.uniform(-1000, 1000, size=n)
        
        # Compute the right-hand side vector b
        b = np.dot(A, x)
        
        # Format the output and write to input.txt
        with open("input.txt", "w") as f:
            # Write equations without constants first
            for row in A:
                f.write("   ".join(map(str, row)) + "\n")
            
            f.write("\n")
            
            # Write constants at the end
            f.write("   ".join(map(str, b)) + "\n")
        
        # Write solution vector x to solutions.txt
        with open("solutions.txt", "w") as f:
            # Write each solution value on a new line
            for value in x:
                f.write(f"{value}\n")
        
    except Exception as e:
        print(f"An error occurred: {e}")

# Read n from command-line arguments
if __name__ == "__main__":
    if len(sys.argv) > 1:
        n = int(sys.argv[1])  # Convert argument to integer
        generate_equations(n)

