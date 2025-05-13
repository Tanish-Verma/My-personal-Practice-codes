import numpy as np
from scipy.integrate import quad
from scipy.optimize import fsolve
import matplotlib.pyplot as plt

# Define the circle and parabola equations
def upper_circle(x):
    return np.sqrt(16 - (x - 5) ** 2) + 6

def lower_circle(x):
    return -np.sqrt(16 - (x - 5) ** 2) + 6

def upper_parabola(x):
    return np.sqrt(4 * x)

def lower_parabola(x):
    return -np.sqrt(4 * x)

# Find intersection points numerically using fsolve
def intersection_upper_eq(x):
    return upper_circle(x) - upper_parabola(x)

def intersection_lower_eq(x):
    return lower_circle(x) - lower_parabola(x)

# Guess initial points for fsolve based on observation
x1_guess = 1
x2_guess = 9

# Solve for x1 and x2 using fsolve for upper and lower curves
x1 = fsolve(intersection_upper_eq, x1_guess)[0]
x2 = fsolve(intersection_lower_eq, x2_guess)[0]

# Ensure that x1 and x2 are valid and lie in the range
if not (0 <= x1 <= 10 and 0 <= x2 <= 10):
    raise ValueError("Intersection points not in the valid range.")

# Define the integrand for the area difference between the curves
def area_diff_upper(x):
    return upper_circle(x) - upper_parabola(x)

def area_diff_lower(x):
    return lower_parabola(x) - lower_circle(x)

# Perform integration for the upper and lower halves
area_upper, _ = quad(area_diff_upper, x1, x2)
area_lower, _ = quad(area_diff_lower, x1, x2)

# Total intersection area
total_area = area_upper + area_lower
print(f"Total Area of Intersection: {total_area}")

# Plot the curves for visualization
x = np.linspace(0, 10, 1000)
y1 = np.sqrt(16 - (x - 5)**2) + 6
y2 = -np.sqrt(16 - (x - 5)**2) + 6
y3 = np.sqrt(4*x)
y4 = -np.sqrt(4*x)

plt.plot(x, y1, label='Upper Circle', color='blue')
plt.plot(x, y2, label='Lower Circle', color='blue')
plt.plot(x, y3, label='Upper Parabola', color='red')
plt.plot(x, y4, label='Lower Parabola', color='red')

# Highlight the area of intersection
plt.fill_between(x, y1, y3, where=(x >= x1) & (x <= x2), color='gray', alpha=0.5, label='Intersection Area')

plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.title('Intersection of Circle and Parabola')
plt.show()
