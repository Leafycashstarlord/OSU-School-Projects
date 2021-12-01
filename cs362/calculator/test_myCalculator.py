import unittest
import myCalculator

class TestCase(unittest.TestCase):
    def test_add(self):
        self.assertEqual(myCalculator.calculate(4, 6, 1), 10)

    def test_add2(self):
        self.assertEqual(myCalculator.calculate(4, 6, 1), 9)

    def test_sub(self):
        self.assertEqual(myCalculator.calculate(10, 7, 2), 3)

    def test_sub2(self):
        self.assertEqual(myCalculator.calculate(10, 7, 2), 4)

    def test_mul(self):
        self.assertEqual(myCalculator.calculate(5, 9, 3), 45)

    def test_mul2(self):
        self.assertEqual(myCalculator.calculate(5, 9, 3), 46)

    def test_div(self):
        self.assertEqual(myCalculator.calculate(8, 2, 4), 4)

    def test_div2(self):
        self.assertEqual(myCalculator.calculate(8, 2, 4), 1)

if __name__ == '__main__':
    unittest.main()