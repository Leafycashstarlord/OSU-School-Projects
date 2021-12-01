import unittest
import fullName

class TestCase(unittest.TestCase):
    def test_realName(self):
        self.assertEqual(fullName.makeName("Jackson", "Rollins"), "Jackson Rollins")

    def test_anyNum(self):
        self.assertTrue(any(map(str.isdigit, fullName.makeName("Jacks0n", "Rollins"))), True)

    def test_allNum(self):
        self.assertEquals(fullName.makeName("123", "456"), "123 456")

if __name__ == '__main__':
    unittest.main()