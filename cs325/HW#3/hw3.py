"""
Jackson E. Rollins
11/18/2021
932932878
"""

import sys

def file_contents_letters(file_name):
    """
    Takes a file name as input and returns a string consisting of the file's contents
    with all non-letter characters removed.
    
    Parameters:
        file_name: The name of the file.
    
    Returns:
        A string with the contents of <file_name> but with all non-letter characters removed.
    """

    f = open(file_name, "r")
    file_contents = f.read()
    f.close()
    return "".join([c for c in file_contents if c.isalpha()])
    
def edit_distance(s1, s2):
    """
    Computes the edit distance between two strings, s1 and s2.
    
    Parameters:
        s1: The first string.
        s2: The second string.
    
    Returns:
        The edit distance between s1 and s2.
    """
    m = len(s1)
    n = len(s2)
    distance = [[0 for i in range(n)] for j in range(m)]

    for i in range(m):
        distance[i][0] = i
    for j in range(n):
        distance[0][j] = j
    
    for i in range(m):
        for j in range(1, n):
            distance[i][j] = min(distance[i - 1][j] + 1, distance[i][j - 1] + 1, distance[i - 1][j - 1] + int(s1[i] != s2[j]))
    
    return distance[m - 1][n - 1]
    
def longest_common_subsequence(s1, s2):
    """
    Computes the length of the longest common subsequence between two strings, s1 and s2.
    
    Parameters:
        s1: The first string.
        s2: The second string.
    
    Returns:
        The length of the longest common subsequence between s1 and s2.
    """
    m = len(s1)
    n = len(s2)
    C = [[None]*(n+1) for i in range(m + 1)]

    for i in range(m + 1):
        for j in range(n + 1):
            if (i == 0) or (j == 0):
                C[i][j] = 0
            elif s1[i - 1] == s2[j - 1]:
                C[i][j] = C[i - 1][j - 1] + 1
            else:
                C[i][j] = max(C[i - 1][j], C[i][j - 1])
    
    return C[m][n]

s1 = file_contents_letters(sys.argv[1])
s2 = file_contents_letters(sys.argv[2])
print(edit_distance(s1, s2), longest_common_subsequence(s1, s2))
