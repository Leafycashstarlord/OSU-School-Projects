import unittest
import wordcount

class test_Cases(unittest.TestCase):
    def test_wordCount(self):
        self.assertEqual(wordcount.countWords("I am Bill"), 3)
    
    def test_wordCount2(self):
        self.assertEqual(wordcount.countWords("1 2 3 4"), 4)

    def test_wordCount3(self):
        self.assertNotEqual(wordcount.countWords("How do you do"), 3)

    def test_wordCount4(self):
        self.assertNotEqual(wordcount.countWords("1 2 345"), 4)

if __name__ == '__main__':
    unittest.main()