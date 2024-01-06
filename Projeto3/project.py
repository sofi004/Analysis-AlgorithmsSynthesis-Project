from pulp import *

# Problem
prob = LpProblem("Exemplo", LpMaximize)

# Variables
x1 = LpVariable("x1", 0)
x2 = LpVariable("x2", 0)

# Objective function
prob += 2*x1 - x2

# Constraints
prob += -3*x1 + x2 <= 1
prob += x1 - x2 <= 1
prob += 3*x1 - x2 <= 5

# Solution
status = prob.solve()
print(LpStatus[status])
print("Optimal value: ", value(prob.objective))
for v in prob.variables():
    print(v.name, "=", v.varValue)
