from pulp import *

prob = LpProblem("Problem", LpMaximize)
input_values = input().split()
nb = int(input_values[0])
np = int(input_values[1])
limProd = int(input_values[2])
db = {}
dp = {}

for b in range(nb):
    input_valuesb = input().split()
    l = int(input_valuesb[0])
    c = int(input_valuesb[1])
    x = LpVariable('B' + str(b), 0, upBound = c, cat=LpInteger)
    db.update({b : [l, c, x]})
    
for p in range(np):
    input_valuesp = input().split()
    i = int(input_valuesp[0])
    j = int(input_valuesp[1])
    k = int(input_valuesp[2])
    lp = int(input_valuesp[3])
    y = LpVariable('P' + str(p) , 0, upBound = min(db[i - 1][1], db[j - 1][1], db[k - 1][1]), cat = LpInteger) 
    if (db[i - 1][0] + db[j - 1][0] + db[k - 1][0]) < lp:
        dp.update({p : [i, j, k, lp, y]})
        db[i - 1].append(y)
        db[j - 1].append(y)
        db[k - 1].append(y)

prob += lpSum([cb[0]*cb[2] for cb in db.values()] + [cp[3]*cp[4]for cp in dp.values()]) 

prob += lpSum([cb[2] for cb in db.values()] + [3*cp[4]for cp in dp.values()])<= limProd

for cb in db.values():
    prob += lpSum(cb[2:]) <= cb[1]

prob.solve(GLPK(msg=0))

print(int(value(prob.objective)))
