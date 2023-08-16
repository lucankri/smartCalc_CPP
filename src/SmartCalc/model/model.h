#ifndef SMARTCALC_MODEL_H
#define SMARTCALC_MODEL_H
#include <cmath>
#include <exception>
#include <list>
#include <regex>
#include <stack>
#include <string>
#include <utility>
#include <vector>

namespace s21 {

class CalculationResult;
class GraphResult;

class Model {
  struct Lexeme;
  using list_type = std::list<Model::Lexeme *>;

 public:
  Model();
  ~Model();
  CalculationResult calculateExpression(const std::string &expression,
                                        const double &x);
  GraphResult calculateExpressionGraph(const double &xBegin, const double &xEnd,
                                       const std::string &expression,
                                       const std::size_t &points);

 private:
  void lexemize();
  void searchUnaryOperator();
  void reversePolishNotation();
  double calculateExpressionRpn(const double &x);
  static void applyFunction(const Lexeme *lex, std::stack<Lexeme *> &stack,
                            const double &x);
  static void applyOperator(const Lexeme *lex, std::stack<Lexeme *> &stack,
                            const double &x);
  static Lexeme *createLexeme(const std::string &str_lexeme);
  static Lexeme *createValue(const double &v);
  static Lexeme *createOperator(const char &o);
  static Lexeme *createFunction(const std::string &f);
  static Lexeme *createLeftRightParenthesis(const char &p);
  static Lexeme *createX();
  static void deleteLexemes(list_type &list_lexemes);

  struct Lexeme {
    explicit Lexeme(const char &type, const char &o, std::string f,
                    const double &v);
    /**
     * f: function
     * u: unary - or +
     * o: operation + - * /
     * (: literal (
     * ): literal )
     * v: value
     * x: literal x
     **/
    char type_;
    char o_;
    std::string f_;
    double v_;
  };

  /**
   * Исключения:
   * 0 - все хорошо
   * 1 - ошибка в синтаксисе выражения
   * 2 - неправильно составлено выражение
   * 3 - деление на 0
   * 4 - аргумент в sqrt, log и log10 не может быть отрицательным
   * 5 - пустое выражение
   */
  class CalculationException : public std::exception {
   public:
    explicit CalculationException(const int &error);
    [[nodiscard]] int getError() const;

   private:
    int error_;
  };

  static inline const char *kRegularMathExpression_ =
      R"(([1-9]\d*|0)(\.\d*[0-9])?|\+|-|\*|\^|mod|/|\(|\)|x| |sin|cos|tan|asin|acos|atan|sqrt|ln|log)";
  static inline const char *kRegularValue_ = R"(([1-9]\d*|0)(\.\d*[0-9])?)";
  static inline const char *kRegularOperators_ = R"(\+|-|\*|\^|mod|/)";
  static inline const char *kRegularFunctions_ =
      R"(sin|cos|tan|asin|acos|atan|sqrt|ln|log)";

  std::string math_expression_;
  list_type list_lex_expression_;
};

/**
 * Класс для вывода результата.
 * Коды ошибок одинаковы с CalculationException
 */
class CalculationResult {
  friend CalculationResult Model::calculateExpression(
      const std::string &expression, const double &x);

 public:
  explicit CalculationResult();
  [[nodiscard]] int getError() const;
  [[nodiscard]] double getResult() const;

 private:
  int error_;
  double result_;
};

/**
 * Класс для вывода графика.
 * Коды ошибок одинаковы с CalculationException
 */
class GraphResult {
  friend GraphResult Model::calculateExpressionGraph(
      const double &xBegin, const double &xEnd, const std::string &expression,
      const std::size_t &points);

 public:
  explicit GraphResult();
  [[nodiscard]] std::vector<double> getX() const;
  [[nodiscard]] std::vector<double> getY() const;
  int getError();

 private:
  std::vector<double> x_;
  std::vector<double> y_;
  int error_;
};
}  // namespace s21

#endif  // SMARTCALC_MODEL_H
