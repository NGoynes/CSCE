from unifier import parse_term, App, Var
from intern import intern


def compare(clause1, clause2):
    args1 = extend(clause1)
    args2 = extend(clause2)

    for i in args1:
        if i in args2:
            subst = Var(intern())

            for j in range(0, len(clause2[1])):
                result = parse_term(clause2[1][j])
                result.args = [str(k).replace(str(i), str(subst)) for k in result.args]
                clause2[1][j] = str(result)

            for j in range(0, len(clause2[2])):
                result = parse_term(clause2[2][j])
                result.args = [str(k).replace(str(i), str(subst)) for k in result.args]
                clause2[2][j] = str(result)


def extend(clause):
    args = []
    loc = 0

    for x in clause[1]:
        args.extend(parse_term(x).args)
    for x in clause[2]:
        args.extend(parse_term(x).args)

    while loc < len(args):
        if isinstance(args, App):
            args.extend(args[loc].args)
        loc += 1

    for x in args[:]:
        if not isinstance(x, Var):
            args.remove(x)

    result = []
    for x in args:
        if x not in result:
            result.append(x)

    return result
