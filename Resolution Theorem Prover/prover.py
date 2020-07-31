from unifier import *  # CREDIT GOES TO GITHUB USER ELIBEN FOR THE LEXER AND UNIFIER:
# https://github.com/eliben/code-for-blog/tree/master/2018/unif
from dupeclause import *
from compare import *
from theorems import *


def twopointer(theorem, goalloc):
    innerloop = 0
    outerloop = goalloc - 1
    while True:
        for i in range(innerloop, outerloop):
            j = theorem[i]
            if resolve(theorem, outerloop, j, 1) is True:
                return False
            if resolve(theorem, outerloop, j, 2) is True:
                return False
        outerloop += 1


def resolve(theorem, outer, clause, loc):
    if loc == 1:
        opp = 2
    else:
        opp = 1

    for i in clause[loc]:
        find = i[:i.find('(')]
        for j in theorem[outer][opp]:
            new = j[:j.find('(')]
            curr = theorem[outer][opp].index(j)
            if find == new:
                compare(clause, theorem[outer])
                subst = unify(parse_term(i), parse_term(j), {})
                if subst is not None:
                    found = substitute(theorem, outer, subst, i, clause, loc, opp, curr)
                    return found

    return False


def substitute(theorem, outer, subst, expr, clause, loc, opp, curr):
    if loc == 1:
        pos = clause[loc].copy()
        pos.remove(expr)
        pos.extend(theorem[outer][loc])
        for i in range(0, len(pos)):
            pos[i] = str(apply_unifier(parse_term(pos[i]), subst))

        neg = theorem[outer][opp].copy()
        neg.remove(theorem[outer][opp][curr])
        neg.extend(clause[opp])
        for i in range(0, len(neg)):
            neg[i] = str(apply_unifier(parse_term(neg[i]), subst))
    else:
        neg = clause[loc].copy()
        neg.remove(expr)
        neg.extend(theorem[outer][loc])
        for i in range(0, len(neg)):
            neg[i] = str(apply_unifier(parse_term(neg[i]), subst))

        pos = theorem[outer][opp].copy()
        pos.remove(theorem[outer][opp][curr])
        pos.extend(clause[opp])
        for i in range(0, len(pos)):
            pos[i] = str(apply_unifier(parse_term(pos[i]), subst))

    new = [len(theorem) + 1, pos, neg]
    if len(pos) == 0:
        if len(neg) == 0:
            print(new)
            theorem.append(new)
            return True

    if not dupeclause(new, theorem):
        print(new)
        theorem.append(new)

    return False


if __name__ == '__main__':
    print("Welcome to the Resolution Theorem Prover!")
    print("Current theorems are:\n\'howling 6 (where 6 is the goal location)\', \'rr 7\' (roadrunner), \'customs 7\', "
          "\'harmonia 7\', and my own custom theorem called \'user 8\'.")
    call = input("Please enter a theorem and the goal location (e.g. \"rr 7\" or \"howling 6\"): ")
    theorem = call[0:call.find(' ', 0, len(call))]
    goal = call[call.find(' ', 0, len(call)) + 1:len(call)]
    print("\nResolution Steps:")

    caller = {'howling': howling,
              'rr': rr,
              'customs': customs,
              'harmonia': harmonia,
              'user': user}

    for x in caller[theorem]:
        print(x)
    solution = twopointer(caller[theorem], int(goal))

    input("Press Enter to Exit")