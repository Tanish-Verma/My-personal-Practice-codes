def factorial(n):
    if n==0 or n==1:
        return 1
    return n*factorial(n-1)

import math as m
sum=0
for i in range(20):
    x=factorial(4*i)*(1103.0+26390*i)
    y=(factorial(i)**4)*396**(4*i)
    z=x/y
    sum+=z
Ramanujun_formula= ((2*m.sqrt(2))*sum/9801.0)
print(1/Ramanujun_formula)
# print(m.pi-1/Ramanujun_formula)