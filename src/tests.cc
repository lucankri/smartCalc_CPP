#include <gtest/gtest.h>

#include "SmartCalc/controller/controller.h"

TEST(Calculate_expression, test_1) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression(
      "5*(30+170)-160/(4*2)+(3700+300-100)/100-500*2", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_EQ(result.getResult(), 19);
}

TEST(Calculate_expression, test_2) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression(
      "(29+31*2-18-10)*9*80-(47+19-8*6)-72/(6*2)-(90-6*9+28)", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_EQ(result.getResult(), 45272);
}

TEST(Calculate_expression, test_3) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression(
      "(960-120*5)/3+28*(3*10)-15*(12/3)*(14*2)*5*5+(48+32)/16+500", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_EQ(result.getResult(), -40535);
}

TEST(Calculate_expression, test_4) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression(
      "(900-60*9+280)/80*50-20*(32-24)/4-(101+99)/100*55/10+(15*8+180)/6*9-320",
      0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_EQ(result.getResult(), 479);
}

TEST(Calculate_expression, test_5) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("2^3", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_EQ(result.getResult(), 8);
}

TEST(Calculate_expression, test_6) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("2mod(+3)", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_EQ(result.getResult(), 2);
}

TEST(Calculate_expression, test_7) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("5mod3", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_EQ(result.getResult(), 2);
}

TEST(Calculate_expression_x, test_1) {
  s21::Model model;
  s21::Controller controller(&model);
  double x = 12.36;
  auto result = controller.calculateExpression(
      "5*(x+170)-160/(x*2)+(x+300-100)/100-500*2", x);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_DOUBLE_EQ(result.getResult(), -92.54889190938502);
}

TEST(Calculate_expression_x, test_2) {
  s21::Model model;
  s21::Controller controller(&model);
  double x = 8;
  auto result = controller.calculateExpression(
      "5*(x+170)-160/(x*2)+(x+300-100)/100-500*2", x);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_DOUBLE_EQ(result.getResult(), -117.91999999999996);
}

TEST(Calculate_expression_x, test_3) {
  s21::Model model;
  s21::Controller controller(&model);
  double x = 2;
  auto result = controller.calculateExpression("2*(x+2)", x);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_EQ(result.getResult(), 8);
}

TEST(Calculate_expression_x, test_4) {
  s21::Model model;
  s21::Controller controller(&model);
  double x = 2;
  auto result = controller.calculateExpression("2*(x+2)/x", x);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_EQ(result.getResult(), 4);
}

TEST(Calculate_expression_functions, test_1) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("sin(2)", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_DOUBLE_EQ(result.getResult(), 0.90929742682568171);
}

TEST(Calculate_expression_functions, test_2) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("cos(2)", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_DOUBLE_EQ(result.getResult(), -0.41614683654714241);
}

TEST(Calculate_expression_functions, test_3) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("tan(2)", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_DOUBLE_EQ(result.getResult(), -2.1850398632615189);
}

TEST(Calculate_expression_functions, test_4) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("sin(2)^cos(2+1)", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_DOUBLE_EQ(result.getResult(), 1.0987042075494742);
}

TEST(Calculate_expression_functions, test_5) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("sqrt(25)", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_DOUBLE_EQ(result.getResult(), 5);
}

TEST(Calculate_expression_functions, test_6) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("ln(2)", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_DOUBLE_EQ(result.getResult(), 0.69314718055994529);
}

TEST(Calculate_expression_functions, test_7) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("log(2)", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_DOUBLE_EQ(result.getResult(), 0.3010299956639812);
}

TEST(Calculate_expression_functions, test_8) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("asin(1)", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_DOUBLE_EQ(result.getResult(), 1.5707963267948966);
}

TEST(Calculate_expression_functions, test_9) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("acos(1)", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_DOUBLE_EQ(result.getResult(), 0);
}

TEST(Calculate_expression_functions, test_10) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("atan(1)", 0);
  ASSERT_EQ(result.getError(), 0);
  ASSERT_DOUBLE_EQ(result.getResult(), 0.78539816339744828);
}

TEST(Calculate_expression_error, test_1) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("atan(1+3", 0);
  ASSERT_EQ(result.getError(), 1);
}

TEST(Calculate_expression_error, test_2) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("atan3)-1", 0);
  ASSERT_EQ(result.getError(), 1);
}

TEST(Calculate_expression_error, test_3) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("atan(3)+", 0);
  ASSERT_EQ(result.getError(), 2);
}

TEST(Calculate_expression_error, test_4) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("atan(3)+sin(3^)", 0);
  ASSERT_EQ(result.getError(), 2);
}

TEST(Calculate_expression_error, test_5) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("3/0", 0);
  ASSERT_EQ(result.getError(), 3);
}

TEST(Calculate_expression_error, test_6) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("3mod0", 0);
  ASSERT_EQ(result.getError(), 3);
}

TEST(Calculate_expression_error, test_7) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("sqrt(-5)", 0);
  ASSERT_EQ(result.getError(), 4);
}

TEST(Calculate_expression_error, test_8) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("ln(-5)", 0);
  ASSERT_EQ(result.getError(), 4);
}

TEST(Calculate_expression_error, test_9) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("", 0);
  ASSERT_EQ(result.getError(), 5);
}

TEST(Calculate_expression_error, test_10) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("2+3-sin", 0);
  ASSERT_EQ(result.getError(), 1);
}

TEST(Calculate_expression_error, test_11) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("log(-4)", 0);
  ASSERT_EQ(result.getError(), 4);
}

TEST(Calculate_expression_error, test_12) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("2+2+2 3 3", 0);
  ASSERT_EQ(result.getError(), 2);
}

TEST(Calculate_expression_error, test_13) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result = controller.calculateExpression("+", 0);
  ASSERT_EQ(result.getError(), 2);
}

TEST(Calculate_expression_graph, test_1) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result1 = controller.calculateGraph(-10, 10, "sin(x)", 10);
  auto result2 = controller.calculateGraph(-10, 10, "sin(x)", 10);
  ASSERT_EQ(result1.getError(), 0);
  ASSERT_EQ(result2.getError(), 0);
  for (int i = 0; i < 10; i++) {
    ASSERT_EQ(result1.getX()[i], result2.getX()[i]);
    ASSERT_EQ(result1.getY()[i], result2.getY()[i]);
  }
}

TEST(Calculate_expression_graph, test_2) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result1 = controller.calculateGraph(-10, 10, "log(x)", 10);
  auto result2 = controller.calculateGraph(-10, 10, "log(x)", 10);
  ASSERT_EQ(result1.getError(), 0);
  ASSERT_EQ(result2.getError(), 0);
}

TEST(Calculate_expression_graph_error, test_1) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result1 = controller.calculateGraph(-10, 10, "log(x+wer", 10);
  auto result2 = controller.calculateGraph(-10, 10, "log(x+wer", 10);
  ASSERT_EQ(result1.getError(), 1);
  ASSERT_EQ(result2.getError(), 1);
}

TEST(Calculate_expression_graph_error, test_2) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result1 = controller.calculateGraph(-10, 10, "log(x)+*", 10);
  auto result2 = controller.calculateGraph(-10, 10, "log(x)+*", 10);
  ASSERT_EQ(result1.getError(), 2);
  ASSERT_EQ(result2.getError(), 2);
}

TEST(Calculate_expression_graph_error, test_3) {
  s21::Model model;
  s21::Controller controller(&model);
  auto result1 = controller.calculateGraph(-10, 10, "", 10);
  auto result2 = controller.calculateGraph(-10, 10, "", 10);
  ASSERT_EQ(result1.getError(), 5);
  ASSERT_EQ(result2.getError(), 5);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
