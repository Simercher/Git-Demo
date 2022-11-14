package com.github.simercher;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

class CustomCalculatorTest {

  CustomCalculator calculator;

  @BeforeEach
  void setUp() {
    calculator = new CustomCalculator();
  }

  @Test
  void add() {
    int a = 1;
    int b = 2;

    int actual = calculator.add(a, b);
    int ecpected = 3;

    assertEquals(ecpected, actual);
  }
}
