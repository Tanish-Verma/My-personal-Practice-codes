import numpy as np
import sympy as sp

# Define the variable
x = sp.symbols('x')

# Create a polynomial with roots at x = 1 and x = -1
base_polynomial = (x - 1) * (x + 1)

# Multiply by another polynomial to increase the degree to 10
polynomial = base_polynomial * (x**8 + 1)

# Simplify the polynomial
polynomial = sp.simplify(polynomial)

print("Polynomial:", polynomial)

# One real root is x = 1
print("One real root:", 1)
