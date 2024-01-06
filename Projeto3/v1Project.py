from pulp import *

prob = LpProblem("Problem", LpMaximize)
nb, np, limProd = map(int, input().split())
db = {}
dp = {}

for b in range(nb):
    l , c = map(int, input().split())
    x = LpVariable(b, 0, upBound = c, cat=LpInteger)
    db.update({b : [l, c, x]})
    
for p in range(np):
    i, j, k, lp = map(int, input().split())
    x = LpVariable(p, 0, upBound = min(db[i][1], db[j][1], db[k][1]), cat = LpInteger) 
    if (db[i][0] + db[j][0] + db[k][0]) < lp:
        dp.update({p : [i, j, k, lp, x]})
        db[i] += [x]
        db[i] += [x]
        db[i] += [x]

prob += lpSum([cb[0]*cb[2] for cb in db] + [cp[3]*cp[4]for cp in dp]) 

prob += lpsum([cb[2] for cb in db] + [3*cp[4]for cp in dp]) <= limProd

for cb in db:
    prob += lpsum(cb[2:]) <= cb[1]

model.solve(GLPK(msg=0))

print(int(value(prob.objective)))
