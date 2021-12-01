"""
Jackson E. Rollins 6/6/2021 - Tests for calc app
"""
import calculator


class Test_CalculatorApp:
    def test_add(self):
        assert 5 == calculator.add(3, 2)

    def test_subtract(self):
        assert 1 == calculator.subtract(3, 2)

    def test_multiply(self):
        assert 20 == calculator.multiply(4, 5)

    def test_division(self):
        assert 2 == calculator.division(10, 5)
