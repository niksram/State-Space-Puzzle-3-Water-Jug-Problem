Problem:

    There are 3 water jugs with different maximum capacity. 
    Initially the 3 jugs are filled to a certain quantity. The final state to be attained are also given.
    We are allowed to pour contents of any jug 'source' to any other jug 'destination'.
    Using these available combinations, we must find all the solutions possible

Solving Strategy:

    Here, the implementation is based on State-Space-Search. This gives the result based on DFS traversal.
    The doubly linked list is used to mimic the functioning of the Recursive Stack.       