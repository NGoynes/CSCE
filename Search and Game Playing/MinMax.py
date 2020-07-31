from queue import LifoQueue

ex = [1, [5, 7], 4]
one = [[4, [7, 9, 8], 8], [[[3, 6, 4], 2, 6], [[9, 2, 9], 4, 7, [6, 4, 5]]]]
two = [[[1, 4], [3, [5, 2, 8, 0], 7, [5, 7, 1]], [8, 3]], [[[3, 6, 4], 2, [9, 3, 0]], [[8, 1, 9], 8, [3, 4]]]]
three = [5, [[[4, 7, -2], 7], 6]]
four = [[8, [7, 9, 8], 4], [[[3, 6, 4], 2, 1], [[6, 2, 9], 4, 7, [6, 4, 5]]]]
five = [[[1, [4, 7]], [3, [[5, 2], [2, 8, 9], 0, -2], 7, [5, 7, 1]], [8, 3]], [[[8, [9, 3, 2], 5], 2, [9, [3, 2], 0]], [[3, 1, 9], 8, [3, 4]]]]
root = None
maxdepth = 0

class Node:
    def __init__(self, val=None, depth=0, path=[], parent=None, children=[]):
        self.val = val
        self.depth = depth
        self.path = path
        self.parent = parent
        self.children = children

    def __lt__(self, other):
        return self.val < other.val

    val = None
    depth = 0
    path = []
    parent = None
    children = []

def buildtree(nodes):
    global root
    root = Node(None, 0, [], None, [])
    return buildtreerec(nodes, 0, 0, None, root)

def buildtreerec(nodes, depth, loc, parent, curr):
    global root, maxdepth
    if depth > maxdepth:
        maxdepth = depth
    if parent is None:
        root = curr
    if isinstance(nodes, int):
        if parent is not None:
            parent.children.append(curr)
            curr.parent = parent
        curr.val = nodes
        curr.path.append(loc)
    else:
        if parent is not None:
            parent.children.append(curr)
            curr.parent = parent
        for count, ele in enumerate(nodes):
            buildtreerec(ele, depth + 1, count + 1, curr, Node(None, depth + 1, curr.path, parent, []))
    return root

def minmaxer(node, depth):
    if depth == 0 or node.val is not None:
        return node

    if depth % 2 == 0:
        recur = []
        for x in node.children:
            recur.append(minmaxer(x, depth - 1))
        maximum = max(recur)
        return maximum
    else:
        recur = []
        for x in node.children:
            recur.append(minmaxer(x, depth - 1))
        minimum = min(recur)
        return minimum

def main():
    global ex, one, two, three, four, five

    print("Tree: ")
    tree = buildtree(ex)
    print(ex)
    solution = minmaxer(tree, maxdepth)
    print("Solution: ", end="")
    print(solution.val)
    print("Path: ", end="")
    for count, ele in enumerate(solution.path):
        print(ele, end=" ")
        if count != len(solution.path) - 1:
            print("->", end=" ")
        else:
            print()
    print()

    print("Tree: ")
    tree = buildtree(one)
    print(one)
    solution = minmaxer(tree, maxdepth)
    print("Solution: ", end="")
    print(solution.val)
    print("Path: ", end="")
    for count, ele in enumerate(solution.path):
        print(ele, end=" ")
        if count != len(solution.path) - 1:
            print("->", end=" ")
        else:
            print()
    print()

    print("Tree: ")
    tree = buildtree(two)
    print(two)
    solution = minmaxer(tree, maxdepth)
    print("Solution: ", end="")
    print(solution.val)
    print("Path: ", end="")
    for count, ele in enumerate(solution.path):
        print(ele, end=" ")
        if count != len(solution.path) - 1:
            print("->", end=" ")
        else:
            print()
    print()

    print("Tree: ")
    tree = buildtree(three)
    print(three)
    solution = minmaxer(tree, maxdepth)
    print("Solution: ", end="")
    print(solution.val)
    print("Path: ", end="")
    for count, ele in enumerate(solution.path):
        print(ele, end=" ")
        if count != len(solution.path) - 1:
            print("->", end=" ")
        else:
            print()
    print()

    print("Tree: ")
    tree = buildtree(four)
    print(four)
    solution = minmaxer(tree, maxdepth)
    print("Solution: ", end="")
    print(solution.val)
    print("Path: ", end="")
    for count, ele in enumerate(solution.path):
        print(ele, end=" ")
        if count != len(solution.path) - 1:
            print("->", end=" ")
        else:
            print()
    print()

    print("Tree: ")
    tree = buildtree(five)
    print(five)
    solution = minmaxer(tree, maxdepth)
    print("Solution: ", end="")
    print(solution.val)
    print("Path: ", end="")
    for count, ele in enumerate(solution.path):
        print(ele, end=" ")
        if count != len(solution.path) - 1:
            print("->", end=" ")
        else:
            print()
    print()

    return 0

main()