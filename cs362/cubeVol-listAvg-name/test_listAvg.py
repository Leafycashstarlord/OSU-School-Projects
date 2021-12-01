import unittest
import listAvg

class TestCase(unittest.TestCase):
    def test_emptyList(self):
        self.assertRaises(ZeroDivisionError, lambda:listAvg.calculateAvg([]))
    
    def test_positiveList(self):
        self.assertEqual(listAvg.calculateAvg([1, 2, 3, 4]), 2.5)

    def test_mixedList(self):
        self.assertEqual(listAvg.calculateAvg([-1, 2, -3, 4]), 0.5)

if __name__ == '__main__':
    unittest.main()