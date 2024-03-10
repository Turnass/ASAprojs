from pulp import *
import time

start_time = time.time()

prob = LpProblem("myProblem", LpMaximize)

t, p, m = map(int, input().split())

profits = 0
produced = []
capacities = []
package_products = {}
n_produced = 0

for i in range(t):
        profit, capacity = map(int, input().split())
        product = LpVariable(f"product_{i}", lowBound=0, upBound=capacity, cat=LpInteger)
        produced.append(product)
        n_produced += product
        profits += profit * product
        capacities.append(capacity)
for i in range(p):
        t1, t2, t3, profit = map(int, input().split())
        package = LpVariable(f"package_{i}", lowBound=0, cat=LpInteger)
        n_produced += 3 * package
        profits += profit * package
        if not t1 in package_products:
            package_products[t1] = package
        else:
            package_products[t1] += package
        if not t2 in package_products:
            package_products[t2] = package
        else:
            package_products[t2] += package
        if not t3 in package_products:
            package_products[t3] = package
        else:
            package_products[t3] += package

for i in package_products:
    prob += produced[i - 1] + package_products[i] <= capacities[i - 1]
prob += n_produced <= m
prob += profits

prob.solve(GLPK(msg=0))

print(int(value(prob.objective)))

end_time = time.time()

elapsed_time = end_time - start_time

print(elapsed_time)