import unittest
import leapyear

class TestCase(unittest.TestCase):
    def test_divFourhun(self):
        self. assertEqual(leapyear.calcLeapYear(2000), "2000 is a Leap Year.")

    def test_divOnehun(self):
        self. assertEqual(leapyear.calcLeapYear(1900), "1900 is not a Leap Year.")
    
    def test_divFour(self):
        self.assertEqual(leapyear.calcLeapYear(2004), "2004 is a Leap Year.")
    
    def test_nodiv(self):
        self. assertEqual(leapyear.calcLeapYear(2001), "2001 is not a Leap Year.")

if __name__ == '__main__':
    unittest.main()