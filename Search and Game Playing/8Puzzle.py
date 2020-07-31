from queue import Queue, LifoQueue, PriorityQueue
from copy import copy
from functools import partial

# The functions should be implemented so that the following
# interface will work
# easy: '(1 3 4 8 6 2 7 0 5)
# medium: '(2 8 1 0 4 3 7 6 5)
# hard: '(5 6 7 4 0 8 3 2 1)

easy = [1, 3, 4, 8, 6, 2, 7, 0, 5]
medium = [2, 8, 1, 0, 4, 3, 7, 6, 5]
hard = [5, 6, 7, 4, 0, 8, 3, 2, 1]

#-------------------------------------------------------------------------------
# global variable: goal
# state
#-------------------------------------------------------------------------------
goal = [1, 2, 3, 8, 0, 4, 7, 6, 5]

 #-------------------------------------------------------------------------------
 # global variables: number of tiles
 #-------------------------------------------------------------------------------
numtiles = 9
numnodes = 0
max = 0

class Node:
    def __init__(self, state=[], h="", hval=0, depth=0, path=[], parent=None, children=[]):
        self.state = state
        self.h = h
        self.hval = hval
        self.depth = depth
        self.path = path
        self.parent = parent
        self.children = children

    def __lt__(self, other):
        return self.hval < other.hval

    state = []
    h = ""
    hval = 0
    depth = 0
    path = []
    parent = None
    children = []

# depth first
# example: (dfs '(1 2 3 4 5 6 7 8 0))
def dfs(state):
    global max
    q = LifoQueue()
    v = []

    curr = Node(state, "", 0, 0, [], None, [])
    q.put(curr)
    v.append(curr.state)
    while True:
        if q.qsize() > max:
            max = q.qsize()
        curr = q.get()
        print(curr.state)
        if curr.state == goal:
            return curr
        else:
            curr = expand(curr)
            for x in curr.children:
                if x.state not in v:
                    v.append(x.state)
                    q.put(x)
    return None

# breadth first
# example: (bfs '(1 2 3 4 5 6 7 8 0))
def bfs(state):
    global max
    q = Queue()
    v = []

    curr = Node(state, "", 0, 0, [], None, [])
    q.put(curr)
    v.append(curr.state)
    while True:
        if q.qsize() > max:
            max = q.qsize()
        curr = q.get()
        if curr.state == goal:
            return curr
        else:
            curr = expand(curr)
            for x in curr.children:
                if x.state not in v:
                    v.append(x.state)
                    q.put(x)
    return None

def dls(state, limit):
    global max
    q = LifoQueue()
    v = []

    curr = Node(state, "", 0, 0, [], None, [])
    q.put(curr)
    v.append(curr.state)
    while True:
        if q.qsize() > max:
            max = q.qsize()
        if q.qsize() != 0:
            curr = q.get()
        elif q.qsize() == 0 and curr.depth + 1 == limit:
            return None
        if curr.state == goal:
            return curr
        elif curr.depth + 1 != limit:
            curr = expand(curr)
            for x in curr.children:
                if x.state not in v:
                    v.append(x.state)
                    q.put(x)
    return None

# iterative deepening search
# example: (ids '(1 2 3 4 5 6 7 8 0))
def ids(state):
    limit = 1
    while True:
        found = dls(state, limit)
        if found:
            return found
        else:
            limit += 1

# heuristic search
#	heuristic-function should be either 'h1 (# tiles out of place)
#	or 'h2 (sum of manhattan distance)
#	example: (heuristic '(1 2 3 4 5 6 7 8 0) 'h1)
# DO NOT IMPLEMENT THIS: (heuristic state heuristic-function)

# greedy
#	heuristic-function should be either 'h1 (# tiles out of place)
#	or 'h2 (sum of manhattan distance)
#	example: (greedy '(1 2 3 4 5 6 7 8 0) 'h1)
def greedy (state, h):
    global max
    q = PriorityQueue()
    v = []

    curr = Node(state, h, 0, 0, [], None, [])
    q.put(curr)
    v.append(curr.state)
    while True:
        if q.qsize() > max:
            max = q.qsize()
        curr = q.get()
        if curr.state == goal:
            return curr
        else:
            curr = expand(curr)
            for x in curr.children:
                if x.state not in v:
                    v.append(x.state)
                    q.put(x)
    return None

# a*
#	heuristic-function should be either 'h1 (# tiles out of place)
#	or 'h2 (sum of manhattan distance)
# example: (astar '(1 2 3 4 5 6 7 8 0) 'h1)
def astar (state, h):
    return greedy(state, "h3" + h)

# All functions should return a sequence of moves: (UP DOWN ....),
# and it is not necessary for you to print out the solution using
# print-answer, etc.
def expand(node):
    if applicable("up", node):
        opstate = node.state[:]
        newstate = apply_op("up", opstate)
        newdepth = node.depth + 1
        newpath = node.path[:]
        new = Node(newstate, node.h, hcalc(newstate, node.h, newdepth), newdepth, newpath, node, [])
        new.path.append("up")
        node.children.append(new)
    if applicable("down", node):
        opstate = node.state[:]
        newstate = apply_op("down", opstate)
        newdepth = node.depth + 1
        newpath = node.path[:]
        new = Node(newstate, node.h, hcalc(newstate, node.h, newdepth), newdepth, newpath, node, [])
        new.path.append("down")
        node.children.append(new)
    if applicable("left", node):
        opstate = node.state[:]
        newstate = apply_op("left", opstate)
        newdepth = node.depth + 1
        newpath = node.path[:]
        new = Node(newstate, node.h, hcalc(newstate, node.h, newdepth), newdepth, newpath, node, [])
        new.path.append("left")
        node.children.append(new)
    if applicable("right", node):
        opstate = node.state[:]
        newstate = apply_op("right", opstate)
        newdepth = node.depth + 1
        newpath = node.path[:]
        new = Node(newstate, node.h, hcalc(newstate, node.h, newdepth), newdepth, newpath, node, [])
        new.path.append("right")
        node.children.append(new)
    return node

#-------------------------------------------------------------------------------
# Look if op is applicable to state
#-------------------------------------------------------------------------------
def applicable(op, node):
    curr = copy(node)
    blank = curr.state.index(0)
    if op == "up":
        if 0 <= blank <= 2:
            return False
        else:
            return True
    if op == "down":
        if 6 <= blank <= 8:
            return False
        else:
            return True
    if op == "left":
        if blank % 3 == 0:
            return False
        else:
            return True
    if op == "right":
        if blank % 3 == 2:
            return False
        else:
            return True

#-------------------------------------------------------------------------------
# Apply op to state
#-------------------------------------------------------------------------------
def apply_op(op, state):
    global numnodes
    blank = state.index(0)
    numnodes += 1
    if op == "up":
        state[blank], state[blank - 3] = state[blank - 3], state[blank]
        return state
    if op == "down":
        state[blank], state[blank + 3] = state[blank + 3], state[blank]
        return state
    if op == "left":
        state[blank], state[blank - 1] = state[blank - 1], state[blank]
        return state
    if op == "right":
        state[blank], state[blank + 1] = state[blank + 1], state[blank]
        return state

# this is a dummy heuristic function write your own
# this function is needed in (apply - op..) above
def hcalc(state, h, depth):
    hval = 0
    if h == "h1":
        for (x1, x2) in zip(state, goal):
            if x1 != x2:
                hval += 1
        return hval
    elif h == "h2":
        tot = 0
        for x in range(1, numtiles):
            x1 = state.index(x)
            x2 = goal.index(x)
            hval += abs(x1 % 3 - x2 % 3) + abs(x1 // 3 - x2 // 3)
        return hval
    elif h == "h3h1":
        return hcalc(state, "h1", depth) + depth
    elif h == "h3h2":
        return hcalc(state, "h2", depth) + depth

def main():
    global easy, medium, hard, max
    call = input("Enter a search algorithm and a puzzle (e.g. \"dfs (1 2 3 4 5 6 7 8 0)\" or \"dfs easy\") ")
    func = call[0:call.find(' ', 0, len(call))]
    func = func.replace(" ", "")

    if call.find("easy", 0, len(call)) != -1:
        state = easy
        heur = ""
        if (func == "astar" or func == "greedy"):
            heur = call[call.find('h', 0, len(call)) - 1:len(call)]
            heur = heur.replace(" ", "")
    elif call.find("medium", 0, len(call)) != -1:
        state = medium
        heur = ""
        if (func == "astar" or func == "greedy"):
            heur = call[call.find('h', 0, len(call)) - 1:len(call)]
            heur = heur.replace(" ", "")
    elif call.find("hard", 0, len(call)) != -1:
        state = hard
        heur = ""
        if (func == "astar" or func == "greedy"):
            heur = call[call.find('h', call.find('h', 0, len(call)) + 1, len(call)) - 1:len(call)]
            heur = heur.replace(" ", "")
    else:
        list = call[call.find('(', 2, len(call)) + 1:call.find(')', 0, len(call) - 2)]
        heur = ""
        if (func == "astar" or func == "greedy"):
            heur = call[call.find(')', 10, len(call)) + 1:len(call)]
            heur = heur.replace(" ", "")
        list = list.replace(" ", "")
        state = []
        for x in list:
            state.append(int(x))

    caller = {'astar': partial(astar, state=state, h=heur),
              'greedy': partial(greedy, state=state, h=heur),
              'dfs': partial(dfs, state=state),
              'ids': partial(ids, state=state),
              'bfs': partial(bfs, state=state)}
    solution = caller[func]()

    print("Solution found: ", end=" ")
    print(solution.state)
    print("Path to get to solution: ")
    for count, ele in enumerate(solution.path):
        print(ele, end=" ")
        if count != len(solution.path) - 1:
            print("->", end=" ")
        else:
            print()
    print("Number of nodes visited: ", end=" ")
    print(numnodes)
    print("The maximum length of the node list was: ", end=" ")
    print(max)
    return 0

main()

