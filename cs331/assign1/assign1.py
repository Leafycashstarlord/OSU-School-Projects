import sys
import copy
import math
import os
from queue import PriorityQueue
sys.setrecursionlimit(5000)

class State:
    def __init__(self):
        self.leftChicken = 0
        self.leftWolf = 0
        self.leftBoat = 0
        self.rightChicken = 0
        self.rightWolf = 0
        self.rightBoat = 0
        self.parent = None
    
    def __eq__(self, other):
        if (self.rightBoat == other.rightBoat) and (self.rightWolf == other.rightWolf) and (self.rightChicken == other.rightChicken) and (self.leftBoat == other.leftBoat) and (self.leftWolf == other.leftWolf) and (self.leftChicken == other.leftChicken):
            return True
        else:
            return False
    
    def __lt__(self, other):
        if self.heuristic() < other.heuristic():
            return True
        else:
            return False
    
    def __gt__(self, other):
        if self.heuristic() > other.heuristic():
            return True
        else:
            return False
    
    def heuristic(self):
        heur = 2 * (self.rightChicken + self.rightWolf)
        return heur

frontierD = []
exploredD = []
frontierB = []
exploredB = []

def printList(list_a):
    for i in range(0,len(list_a)):
        print("r_w: " + str(list_a[i][0]) + " r_c: " + str(list_a[i][1]) + " b: " + str(list_a[i][2]) + " l_w: " + str(list_a[i][3]) + " l_c: " + str(list_a[i][4]))

def checkDFS(right_w, right_c,boat):
    for i in range(len(exploredD)):
        if exploredD[i][3] == right_w and exploredD[i][4] == right_c and exploredD[i][2] ==boat:
            return 0
    return 1

def checkBFS(right_w, right_c,boat):
    for i in range(len(exploredB)):
        if exploredB[i][3] == right_w and exploredB[i][4] == right_c and exploredB[i][2] ==boat:
            return 0
    return 1

#[right_wolf, right_chicken, boat, left_wolf,left_chicken,parent]
def uninformedDFS(wolf,chicken,output):
    init = [int(wolf),int(chicken),int(1),int(0),int(0),[]]
    newFile = open(output, 'a')
    newFile.write('DFS: \n')
    if wolf ==0 and chicken == 0:
        return init
    frontierD.append(init)
    exploredD.append(init)
    num_nodes = 0
    run = 1
    while run:
        popped = frontierD.pop()
        if popped[0] == 0 and popped[1] == 0:
            solution = []
            while popped:
                solution.insert(0,popped)
                popped = popped[5]
            print("solution: ")
            printList(solution)
            for i in range(0,len(solution)):
                newFile.write("r_w: " + str(solution[i][0]) + " r_c: " + str(solution[i][1]) + " b: " + str(solution[i][2]) + " l_w: " + str(solution[i][3]) + " l_c: " + str(solution[i][4]) + "\n")
            print("nodes expanded: " + str(num_nodes))
            newFile.write("num nodes expanded: " + str(num_nodes) + "\n")
            print("num_steps: " + str(len(solution)))
            newFile.write("num_steps: " + str(len(solution)))
            newFile.close()
            return popped
        else:
            num_nodes+=1
            if popped[2]:
                if popped[1] >= 1 and (popped[1] - 1 >= popped[0] or popped[1] - 1 == 0) and popped[3] <= popped[4] + 1 and checkDFS(popped[3], popped[4] + 1, 0):
                    new = [popped[0],popped[1]-1,0,popped[3],popped[4]+1,popped]
                    frontierD.append(new)
                    exploredD.append(new)
                if popped[1] >= 2 and (popped[1] - 2 >= popped[0] or popped[1] - 2 == 0) and popped[3] <= popped[4] + 2 and checkDFS(popped[3], popped[4] + 2, 0):
                    new = [popped[0],popped[1]-2,0,popped[3],popped[4]+2,popped]
                    frontierD.append(new)
                    exploredD.append(new)
                if popped[0] >= 1 and (popped[3] + 1 <= popped[4] or popped[4] == 0) and checkDFS(popped[3] + 1, popped[4], 0):
                    new = [popped[0]-1,popped[1],0,popped[3]+1,popped[4],popped]
                    frontierD.append(new)
                    exploredD.append(new)
                if popped[0] >= 1 and popped[1] >= 1 and popped[3] + 1 <= popped[4] + 1 and checkDFS(popped[3] + 1, popped[4] + 1, 0):
                    new = [popped[0]-1,popped[1]-1,0,popped[3]+1,popped[4]+1,popped]
                    frontierD.append(new)
                    exploredD.append(new)
                if popped[0] >= 2 and (popped[3] + 2 <= popped[4] or popped[4] == 0) and checkDFS(popped[3] + 2, popped[4], 0):
                    new = [popped[0]-2,popped[1],0,popped[3]+2,popped[4],popped]
                    frontierD.append(new)
                    exploredD.append(new)    
            else:
                if popped[4] >= 1 and (popped[4] - 1 >= popped[3] or popped[4] - 1 == 0) and popped[0] <= popped[1] + 1 and checkDFS(popped[0], popped[1] + 1, 1):
                    new = [popped[0],popped[1]+1,1,popped[3],popped[4]-1,popped]
                    frontierD.append(new)
                    exploredD.append(new)
                if popped[4] >= 2 and (popped[4] - 2 >= popped[3] or popped[4] - 2 == 0) and popped[0] <= popped[1] + 2 and checkDFS(popped[3], popped[4] - 2, 1):
                    new = [popped[0],popped[1]+2,1,popped[3],popped[4]-2,popped]
                    frontierD.append(new)
                    exploredD.append(new)
                if popped[3] >= 1 and (popped[0] + 1 <= popped[1] or popped[1] == 0) and checkDFS(popped[3] - 1, popped[4], 1):
                    new = [popped[0]+1,popped[1],1,popped[3]-1,popped[4],popped]
                    frontierD.append(new)
                    exploredD.append(new)
                if popped[3] >= 1 and popped[4] >= 1 and popped[0] + 1 <= popped[1] + 1 and checkDFS(popped[3] - 1, popped[4] - 1, 1):
                    new = [popped[0]+1,popped[1]+1,1,popped[3]-1,popped[4]-1,popped]
                    frontierD.append(new)
                    exploredD.append(new)
                if popped[3] >= 2 and (popped[0] + 2 <= popped[1] or popped[1] == 0) and checkDFS(popped[3] - 2, popped[4], 1):
                    new = [popped[0]+2,popped[1],1,popped[3]-2,popped[4],popped]
                    frontierD.append(new)
                    exploredD.append(new)
                    
#[right_wolf, right_chicken, boat, left_wolf,left_chicken,parent]
def uninformedBFS(wolf,chicken,output):
    init = [int(wolf),int(chicken),int(1),int(0),int(0),[]]
    newFile = open(output, 'a')
    newFile.write('BFS: \n')
    if wolf ==0 and chicken == 0:
        return init
    frontierB.append(init)
    exploredB.append(init)
    num_nodes = 0
    run = 1
    while run:
        popped = frontierB.pop()
        if popped[0] == 0 and popped[1] == 0:
            solution = []
            while popped:
                solution.insert(0,popped)
                popped = popped[5]
            print("solution: ")
            printList(solution)
            for i in range(0,len(solution)):
                newFile.write("r_w: " + str(solution[i][0]) + " r_c: " + str(solution[i][1]) + " b: " + str(solution[i][2]) + " l_w: " + str(solution[i][3]) + " l_c: " + str(solution[i][4]) + "\n")
            print("nodes expanded: " + str(num_nodes))
            newFile.write("num nodes expanded: " + str(num_nodes) + "\n")
            print("num_steps: " + str(len(solution)))
            newFile.write("num_steps: " + str(len(solution)))
            newFile.close()
            return popped
        else:
            num_nodes+=1
            if popped[2]:
                if popped[1] >= 1 and (popped[1] - 1 >= popped[0] or popped[1] - 1 == 0) and popped[3] <= popped[4] + 1 and checkBFS(popped[3], popped[4] + 1, 0):
                    new = [popped[0],popped[1]-1,0,popped[3],popped[4]+1,popped]
                    frontierB.insert(0,new)
                    exploredB.insert(0,new)
                if popped[1] >= 2 and (popped[1] - 2 >= popped[0] or popped[1] - 2 == 0) and popped[3] <= popped[4] + 2 and checkBFS(popped[3], popped[4] + 2, 0):
                    new = [popped[0],popped[1]-2,0,popped[3],popped[4]+2,popped]
                    frontierB.insert(0,new)
                    exploredB.insert(0,new)
                if popped[0] >= 1 and (popped[3] + 1 <= popped[4] or popped[4] == 0) and checkBFS(popped[3] + 1, popped[4], 0):
                    new = [popped[0]-1,popped[1],0,popped[3]+1,popped[4],popped]
                    frontierB.insert(0,new)
                    exploredB.insert(0,new)                    
                if popped[0] >= 1 and popped[1] >= 1 and popped[3] + 1 <= popped[4] + 1 and checkBFS(popped[3] + 1, popped[4] + 1, 0):
                    new = [popped[0]-1,popped[1]-1,0,popped[3]+1,popped[4]+1,popped]
                    frontierB.insert(0,new)
                    exploredB.insert(0,new)   
                if popped[0] >= 2 and (popped[3] + 2 <= popped[4] or popped[4] == 0) and checkBFS(popped[3] + 2, popped[4], 0):
                    new = [popped[0]-2,popped[1],0,popped[3]+2,popped[4],popped]
                    frontierB.insert(0,new)
                    exploredB.insert(0,new)

            else:
                if popped[4] >= 1 and (popped[4] - 1 >= popped[3] or popped[4] - 1 == 0) and popped[0] <= popped[1] + 1 and checkBFS(popped[0], popped[1] + 1, 1):
                    new = [popped[0],popped[1]+1,1,popped[3],popped[4]-1,popped]
                    frontierB.insert(0,new)
                    exploredB.insert(0,new)
                if popped[4] >= 2 and (popped[4] - 2 >= popped[3] or popped[4] - 2 == 0) and popped[0] <= popped[1] + 2 and checkBFS(popped[3], popped[4] - 2, 1):
                    new = [popped[0],popped[1]+2,1,popped[3],popped[4]-2,popped]
                    frontierB.insert(0,new)
                    exploredB.insert(0,new)                
                if popped[3] >= 1 and (popped[0] + 1 <= popped[1] or popped[1] == 0) and checkBFS(popped[3] - 1, popped[4], 1):
                    new = [popped[0]+1,popped[1],1,popped[3]-1,popped[4],popped]
                    frontierB.insert(0,new)
                    exploredB.insert(0,new)
                if popped[3] >= 1 and popped[4] >= 1 and popped[0] + 1 <= popped[1] + 1 and checkBFS(popped[3] - 1, popped[4] - 1, 1):
                    new = [popped[0]+1,popped[1]+1,1,popped[3]-1,popped[4]-1,popped]
                    frontierB.insert(0,new)
                    exploredB.insert(0,new)
                if popped[3] >= 2 and (popped[0] + 2 <= popped[1] or popped[1] == 0) and checkBFS(popped[3] - 2, popped[4], 1):
                    new = [popped[0]+2,popped[1],1,popped[3]-2,popped[4],popped]
                    frontierB.insert(0,new)
                    exploredB.insert(0,new)

def readFile(file):
    newFile = open(file, 'r')
    temp = []
    state = State()
    lines = newFile.readlines()
    for eachLine in lines:
        line = []
        for i in eachLine.split(','):
            line.append(int(i))
        temp.append(line)
    newFile.close()

    state.leftChicken = temp[0][0]
    state.leftWolf = temp[0][1]
    state.leftBoat = temp[0][2]
    state.rightChicken = temp[1][0]
    state.rightWolf = temp[1][1]
    state.rightBoat = temp[1][2]

    return state

def printState(state):
    print('r_w: '+ str(state.rightWolf) + ' r_c: ' + str(state.rightChicken) + ' b: ' + str(state.rightBoat) + ' l_w: ' + str(state.leftWolf) + ' l_c: ' + str(state.leftChicken))

def writeState(state):
    return ('r_w: '+ str(state.rightWolf) + ' r_c: ' + str(state.rightChicken) + ' b: ' + str(state.rightBoat) + ' l_w: ' + str(state.leftWolf) + ' l_c: ' + str(state.leftChicken))

def moreWolf(state):
    if ((state.leftChicken >= state.leftWolf) or (state.leftChicken == 0)) and ((state.rightChicken >= state.rightWolf) or (state.rightChicken == 0)):
        return True
    else:
        return False

def noNeg(state):
    if(state.leftChicken >= 0) and (state.leftWolf >= 0) and (state.rightChicken >= 0) and (state.rightWolf >= 0):
        return True
    else:
        return False

def noVisit(temp, visited):
    for tempState in visited:
        if tempState.leftWolf == temp.leftWolf and tempState.leftBoat == temp.leftBoat:
            return False
    return True

def move(side, thing, number, state):
    if side == 'right':
        if thing == 0:
            state.leftChicken -= number
            state.rightChicken += number
            state.leftWolf -= number
            state.rightWolf += number
        elif thing == 1:
            state.leftChicken -= number
            state.rightChicken += number
        else:
            state.leftWolf -= number
            state.rightWolf += number
        
        state.leftBoat -= 1
        state.rightBoat += 1

    else:
        if thing == 0:
            state.leftChicken += number
            state.rightChicken -= number
            state.leftWolf += number
            state.rightWolf -= number
        elif thing == 1:
            state.leftChicken += number
            state.rightChicken -= number
        else:
            state.leftWolf += number
            state.rightWolf -= number
        
        state.leftBoat += 1
        state.rightBoat -= 1

def validMove(current):
    moveSet = []
    for i in range(0, 5):
        temp = copy.deepcopy(current)

        if temp.leftBoat == 1:
            if i == 0:
                move('right', 1, 1, temp)
                if moreWolf(temp) and noNeg(temp):
                    temp.parent = current
                    moveSet.append(temp)
            elif i == 1:
                move('right', 1, 2, temp)
                if moreWolf(temp) and noNeg(temp):
                    temp.parent = current
                    moveSet.append(temp)
            elif i == 2:
                move('right', 2, 1, temp)
                if moreWolf(temp) and noNeg(temp):
                    temp.parent = current
                    moveSet.append(temp)
            elif i == 3:
                move('right', 0, 1, temp)
                if moreWolf(temp) and noNeg(temp):
                    temp.parent = current
                    moveSet.append(temp)
            elif i == 4:
                move('right', 2, 2, temp)
                if moreWolf(temp) and noNeg(temp):
                    temp.parent = current
                    moveSet.append(temp)
        else:
            if i == 0:
                move('left', 1, 1, temp)
                if moreWolf(temp) and noNeg(temp):
                    temp.parent = current
                    moveSet.append(temp)
            elif i == 1:
                move('left', 1, 2, temp)
                if moreWolf(temp) and noNeg(temp):
                    temp.parent = current
                    moveSet.append(temp)
            elif i == 2:
                move('left', 2, 1, temp)
                if moreWolf(temp) and noNeg(temp):
                    temp.parent = current
                    moveSet.append(temp)
            elif i == 3:
                move('left', 0, 1, temp)
                if moreWolf(temp) and noNeg(temp):
                    temp.parent = current
                    moveSet.append(temp)
            elif i == 4:
                move('left', 2, 2, temp)
                if moreWolf(temp) and noNeg(temp):
                    temp.parent = current
                    moveSet.append(temp)
    return moveSet

def endPath(current, startState):
    path = []

    path.append(current)
    while current.parent != startState:
        current = current.parent
        path.insert(0, current)
    path.insert(0, startState)
    return path

def iddfs(wolf, chicken, output):
    for maxDepth in range(0, 100000):
        frontierD = []
        exploredD = []
        init = [int(wolf),int(chicken),int(1),int(0),int(0),[], 0]
        newFile = open(output, 'a')
        newFile.write('DFS: \n')
        if wolf ==0 and chicken == 0:
            return init
        frontierD.append(init)
        exploredD.append(init)
        num_nodes = 0
        run = 1
        while run:
            if len(frontierD) == 0:
                break
            popped = frontierD.pop()
            if popped[0] == 0 and popped[1] == 0:
                solution = []
                while popped:
                    solution.insert(0,popped)
                    popped = popped[5]
                print("solution: ")
                printList(solution)
                for i in range(0,len(solution)):
                    newFile.write("r_w: " + str(solution[i][0]) + " r_c: " + str(solution[i][1]) + " b: " + str(solution[i][2]) + " l_w: " + str(solution[i][3]) + " l_c: " + str(solution[i][4]) + "\n")
                print("nodes expanded: " + str(num_nodes))
                newFile.write("num nodes expanded: " + str(num_nodes) + "\n")
                print("num_steps: " + str(len(solution)))
                newFile.write("num_steps: " + str(len(solution)))
                newFile.close()
                return popped
            else:
                num_nodes+=1
                if popped[2]:
                    if popped[1] >= 1 and (popped[1] - 1 >= popped[0] or popped[1] - 1 == 0) and popped[3] <= popped[4] + 1 and checkDFS(popped[3], popped[4] + 1, 0) and popped[6] + 1 <= maxDepth:
                        new = [popped[0],popped[1]-1,0,popped[3],popped[4]+1,popped, popped[6] + 1]
                        frontierD.append(new)
                        exploredD.append(new)
                    if popped[1] >= 2 and (popped[1] - 2 >= popped[0] or popped[1] - 2 == 0) and popped[3] <= popped[4] + 2 and checkDFS(popped[3], popped[4] + 2, 0) and popped[6] + 1 <= maxDepth:
                        new = [popped[0],popped[1]-2,0,popped[3],popped[4]+2,popped, popped[6] + 1]
                        frontierD.append(new)
                        exploredD.append(new)
                    if popped[0] >= 1 and (popped[3] + 1 <= popped[4] or popped[4] == 0) and checkDFS(popped[3] + 1, popped[4], 0) and popped[6] + 1 <= maxDepth:
                        new = [popped[0]-1,popped[1],0,popped[3]+1,popped[4],popped, popped[6] + 1]
                        frontierD.append(new)
                        exploredD.append(new)
                    if popped[0] >= 1 and popped[1] >= 1 and popped[3] + 1 <= popped[4] + 1 and checkDFS(popped[3] + 1, popped[4] + 1, 0) and popped[6] + 1 <= maxDepth:
                        new = [popped[0]-1,popped[1]-1,0,popped[3]+1,popped[4]+1,popped, popped[6] + 1]
                        frontierD.append(new)
                        exploredD.append(new)
                    if popped[0] >= 2 and (popped[3] + 2 <= popped[4] or popped[4] == 0) and checkDFS(popped[3] + 2, popped[4], 0) and popped[6] + 1 <= maxDepth:
                        new = [popped[0]-2,popped[1],0,popped[3]+2,popped[4],popped, popped[6] + 1]
                        frontierD.append(new)
                        exploredD.append(new)    
                else:
                    if popped[4] >= 1 and (popped[4] - 1 >= popped[3] or popped[4] - 1 == 0) and popped[0] <= popped[1] + 1 and checkDFS(popped[0], popped[1] + 1, 1) and popped[6] + 1 <= maxDepth:
                        new = [popped[0],popped[1]+1,1,popped[3],popped[4]-1,popped, popped[6] + 1]
                        frontierD.append(new)
                        exploredD.append(new)
                    if popped[4] >= 2 and (popped[4] - 2 >= popped[3] or popped[4] - 2 == 0) and popped[0] <= popped[1] + 2 and checkDFS(popped[3], popped[4] - 2, 1) and popped[6] + 1 <= maxDepth:
                        new = [popped[0],popped[1]+2,1,popped[3],popped[4]-2,popped, popped[6] + 1]
                        frontierD.append(new)
                        exploredD.append(new)
                    if popped[3] >= 1 and (popped[0] + 1 <= popped[1] or popped[1] == 0) and checkDFS(popped[3] - 1, popped[4], 1) and popped[6] + 1 <= maxDepth:
                        new = [popped[0]+1,popped[1],1,popped[3]-1,popped[4],popped, popped[6] + 1]
                        frontierD.append(new)
                        exploredD.append(new)
                    if popped[3] >= 1 and popped[4] >= 1 and popped[0] + 1 <= popped[1] + 1 and checkDFS(popped[3] - 1, popped[4] - 1, 1) and popped[6] + 1 <= maxDepth:
                        new = [popped[0]+1,popped[1]+1,1,popped[3]-1,popped[4]-1,popped, popped[6] + 1]
                        frontierD.append(new)
                        exploredD.append(new)
                    if popped[3] >= 2 and (popped[0] + 2 <= popped[1] or popped[1] == 0) and checkDFS(popped[3] - 2, popped[4], 1) and popped[6] + 1 <= maxDepth:
                        new = [popped[0]+2,popped[1],1,popped[3]-2,popped[4],popped, popped[6] + 1]
                        frontierD.append(new)
                        exploredD.append(new)

def astar(startState, endState, outPut):
    newFile = open(outPut, 'a')
    newFile.write('astar: \n')

    allNodes = 0
    visited = []

    pq = PriorityQueue()
    pq.put((startState.heuristic(), startState))

    while pq:
        current = pq.get()[1]
        if current == endState:
            finalPath = endPath(current, startState)
            for states in finalPath:
                printState(states)
            print('End State Reached')
            print('Length of path: ' + str(len(finalPath)))
            print('Number of expanded nodes: ' + str(len(visited)))
            for states in finalPath:
                newFile.write(writeState(states))
            newFile.write('End State Reached\n')
            newFile.write('Length of path: ' + str(len(finalPath)))
            newFile.write('Number of expanded nodes: ' + str(len(visited)))
            newFile.close()
            return
        else:
            visited.append(current)
            
            move = validMove(current)

            for states in move:
                pq.put((states.heuristic(), states))

    print('No Solution')
    return

def main():
    outPut = sys.argv[4]
    mode = sys.argv[3]
    mode = mode.lower()
    startState = readFile(sys.argv[1])
    endState = readFile(sys.argv[2])

    if mode == 'bfs':
        uninformedBFS(startState.rightWolf,startState.rightChicken,outPut)
        print('bfs')
        exit()
    elif mode == 'dfs':
        uninformedDFS(startState.rightWolf,startState.rightChicken,outPut)
        print('dfs')
        exit()
    elif mode == 'iddfs':
        iddfs(startState.rightWolf, startState.rightChicken, outPut)
        print('iddfs')
        exit()
    elif mode == 'astar':
        print('astar')
        astar(startState, endState, outPut)
    
    exit()

main()