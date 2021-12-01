import unittest
import cubeVol

class TestCase(unittest.TestCase):
    def test_positive(self):
        self.assertEqual(cubeVol.calculateVol(10), 1000)

    def test_negative(self):
        self.assertLess(cubeVol.calculateVol(-5), 0)

    def test_letter(self):
        self.assertRaises(TypeError, lambda:cubeVol.calculateVol("a"))

if __name__ == '__main__':
    unittest.main()