"""
Jackson E. Rollins
932932878
10/26/2021
"""

import heapq # Hint: use Python's priority queue class, heapq.

class Node:
    def __init__(self, count, children):
        self.count    = count
        self.children = children
        
    def is_leaf(self):
        return False
        
    def __lt__(self, other):
        return self.count < other.count

    def __eq__(self, other):
        return self.count == other.count
        
class LeafNode(Node):
    def __init__(self, symbol, count):
        super().__init__(count, [])
        self.symbol = symbol
        
    def is_leaf(self):
        return True

class HuffmanCode:
    def __init__(self, F):
        self.C = dict()
        
        heap = []
        for char in F:
            leaf_node = LeafNode(char, F[char])
            heapq.heappush(heap, leaf_node)
        
        while len(heap) > 1:
            minL = heapq.heappop(heap)
            minR = heapq.heappop(heap)

            children = [minL, minR]
            count = minL.count + minR.count

            u = Node(count, children)
            heapq.heappush(heap, u)
        
        self.T = heapq.heappop(heap)
        self.dfs(self.T, '')

    def dfs(self, node, bin_code):
        if node.is_leaf():
            self.C.update({node.symbol:bin_code})
        else:
            self.dfs(node.children[0], bin_code + '0')
            self.dfs(node.children[1], bin_code + '1')

        
    def encode(self, m):
        """
        Uses self.C to encode a binary message.
.    
        Parameters:
            m: A plaintext message.
        
        Returns:
            The binary encoding of the plaintext message obtained using self.C.
        """

        bin_encode = ''
        for char in m:
            bin_encode += self.C[char]
        
        return bin_encode
        
    def decode(self, c):
        """
        Uses self.T to decode a binary message c = encode(m).
.    
        Parameters:
            c: A message encoded in binary using self.encode.
        
        Returns:
            The original plaintext message m decoded using self.T.
        """
        
        str_decode = ''
        bi_code = ''
        dic_key_list = list(self.C.keys())
        dic_val_list = list(self.C.values())

        for char in c:
            bi_code += char
            if bi_code in self.C.values():
                location = dic_val_list.index(bi_code)
                dic_key = dic_key_list[location]
                str_decode += dic_key
                bi_code = ''
        
        return str_decode
        
def get_frequencies(s):
    """
    Computes a frequency table for the input string "s".
    
    Parameters:
        s: A string.
        
    Returns:
        A frequency table F such that F[c] = (# of occurrences of c in s).
    """

    F = dict()
    
    for char in s:
        if char in F:
            F[char] += 1
        else:
            F[char] = 1
            
    return F





freqs = get_frequencies('One ring to rule them all, one ring to find them. One ring to rule them all, and in the darkness bind. In the land of Mordor, where the shadows lie.')
huffmancode = HuffmanCode(freqs)

decode_vari = huffmancode.encode('oregon state rules')
print(decode_vari)
print(huffmancode.decode(decode_vari))