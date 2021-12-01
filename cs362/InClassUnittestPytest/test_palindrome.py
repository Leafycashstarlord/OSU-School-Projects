import unittest
import palindrome

class test_Cases(unittest.TestCase):
    def test_palindrome(self):
        self.assertEqual(palindrome.calcPalindrome("racecar"), True)
    
    def test_palindrome2(self):
        self.assertEqual(palindrome.calcPalindrome("12321"), True)

    def test_palindrome3(self):
        self.assertNotEqual(palindrome.calcPalindrome("hello"), True)

    def test_palindrome4(self):
        self.assertNotEqual(palindrome.calcPalindrome("13579"), True)

if __name__ == '__main__':
    unittest.main()