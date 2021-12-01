#Jackson E. Rollins
#932932878
#10/7/2021

from os import F_OK
import sys
import time

# Usage when run from the command line: python max_subarray_algs.py <filename>.
# Example usage:                        python max_subarray_algs.py num_array_500.txt

file_name = sys.argv[1]

f = open(file_name, "r")
A = [int(num) for num in f.readline().strip().split(" ")]
f.close()

def max_subarray_enumeration(A):
    """
    Computes the value of a maximum subarray of the input array by "enumeration."
    
    Parameters:
        A: A list (array) of n >= 1 integers.
    
    Returns:
        The sum of the elements in a maximum subarray of A.
    """
    n = len(A)
    max_val = -10000

    for i in range(n):
        for j in range(i,n):
            cur_val = 0
            for k in range(i,j-1):
                cur_val += A[k]

            if (cur_val > max_val):
                max_val = cur_val
    return max_val

def max_subarray_iteration(A):
    """
    Computes the value of a maximum subarray of the input array by "iteration."
    
    Parameters:
        A: A list (array) of n >= 1 integers.
    
    Returns:
        The sum of the elements in a maximum subarray of A.
    """
    n = len(A)
    max_val = -10000

    for i in range(n):
        cur_val = 0
        for j in range(i,n):
            cur_val += A[j]
            if (cur_val > max_val):
                max_val=cur_val
    return max_val
  
def max_sub_s_d(A, s, n):
    if(s == n):
        return A[s]

    m = (s + n) // 2

    cur_val = 0
    lval = -10000

    for i in range(m, (s - 1), -1):
        cur_val += A[i]
        if (cur_val > lval):
            lval = cur_val
    
    cur_val = 0
    rval = -10000

    for i in range((m+1), (n + 1)):
        cur_val += A[i]
        if(cur_val>rval):
            rval = cur_val

    return max(max_sub_s_d(A, s, m), max_sub_s_d(A, (m + 1), n), max((lval + rval), lval, rval))

def max_subarray_simplification_delegation(A):
    """
    Computes the value of a maximum subarray of the input array by "simplification and delegation."
    
    Parameters:
        A: A list (array) of n >= 1 integers.
    
    Returns:
        The sum of the elements in a maximum subarray of A.
    """

    return max_sub_s_d(A, 0, len(A)- 1)
    
def max_subarray_recursion_inversion(A):
    """
    Computes the value of a maximum subarray of the input array by "recursion inversion."
    
    Parameters:
        A: A list (array) of n >= 1 integers.
    
    Returns:
        The sum of the elements in a maximum subarray of A.
    """
    n = len(A)
    cur_val = 0
    max_val = -10000
    for i in range(0, n):
        cur_val+=A[i]
        if(cur_val < 0):
            cur_val = 0
        elif(max_val < cur_val):
            max_val = cur_val
    return max_val
  
def time_alg(alg, A):
    """
    Runs an algorithm for the maximum subarray problem on a test array and times how long it takes.
    
    Parameters:
        alg: An algorithm for the maximum subarray problem.
        A: A list (array) of n >= 1 integers.
    
    Returns:
        A pair consisting of the value of alg(A) and the time needed to execute alg(A) in milliseconds.
    """

    start_time = time.monotonic_ns() // (10 ** 6) # The start time in milliseconds.
    max_subarray_val = alg(A)
    end_time   = time.monotonic_ns() // (10 ** 6) # The end time in milliseconds.
    return max_subarray_val, end_time - start_time

for alg in [max_subarray_enumeration, max_subarray_iteration,
            max_subarray_simplification_delegation, max_subarray_recursion_inversion]:
    print(file_name, time_alg(alg, A))

