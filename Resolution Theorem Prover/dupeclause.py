import collections


def dupeclause(clause1, clause2):
    for x in clause2:
        if collections.Counter(x[1]) == collections.Counter(clause1[1]):
            if collections.Counter(x[2]) == collections.Counter(clause1[2]):
                return True
    return False
