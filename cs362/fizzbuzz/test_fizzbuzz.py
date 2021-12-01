import unittest
import fizzbuzz

class TestCase(unittest.TestCase):
    def test_printNum(self):
        self.assertEqual(fizzbuzz.printValue(1), 1)

    def test_printFizz(self):
        self.assertEqual(fizzbuzz.printValue(3), "Fizz")

    def test_printFizz2(self):
        self.assertEqual(fizzbuzz.printValue(5), "Buzz")
    
    def test_printFizz3(self):
        self.assertEqual(fizzbuzz.printValue(15), "FizzBuzz")

if __name__ == '__main__':
    unittest.main()
