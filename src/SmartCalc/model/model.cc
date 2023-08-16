#include "model.h"

namespace s21 {

Model::CalculationException::CalculationException(const int &error)
    : error_(error) {}

int Model::CalculationException::getError() const { return this->error_; }

CalculationResult::CalculationResult() {}

int CalculationResult::getError() const { return this->error_; }

double CalculationResult::getResult() const { return this->result_; }

GraphResult::GraphResult() : error_(int{}) {}

std::vector<double> GraphResult::getX() const { return this->x_; }

std::vector<double> GraphResult::getY() const { return this->y_; }

int GraphResult::getError() { return this->error_; }

Model::Model() : math_expression_(std::string{}), list_lex_expression_() {}

Model::~Model() { Model::deleteLexemes(this->list_lex_expression_); }

Model::Lexeme::Lexeme(const char &type, const char &o, std::string f,
                      const double &v)
    : type_(type), o_(o), f_(std::move(f)), v_(v) {}

void Model::deleteLexemes(list_type &list_lexemes) {
  for (auto *element : list_lexemes) {
    delete element;
  }
  list_lexemes.clear();
}

Model::Lexeme *Model::createValue(const double &v) {
  return new Lexeme('v', char{}, std::string{}, v);
}

Model::Lexeme *Model::createOperator(const char &o) {
  return new Lexeme('o', o, std::string{}, double{});
}

Model::Lexeme *Model::createFunction(const std::string &f) {
  return new Lexeme('f', char{}, f, double{});
}

Model::Lexeme *Model::createLeftRightParenthesis(const char &p) {
  return new Lexeme(p, char{}, std::string{}, double{});
}

Model::Lexeme *Model::createX() {
  return new Lexeme('x', char{}, std::string{}, double{});
}

Model::Lexeme *Model::createLexeme(const std::string &str_lexeme) {
  Lexeme *lex = nullptr;
  if (std::regex_match(str_lexeme, std::regex(Model::kRegularValue_)))
    lex = createValue(std::stod(str_lexeme));
  else if (std::regex_match(str_lexeme, std::regex(Model::kRegularOperators_)))
    lex = createOperator(str_lexeme.c_str()[0]);
  else if (std::regex_match(str_lexeme, std::regex(Model::kRegularFunctions_)))
    lex = createFunction(str_lexeme);
  else if (str_lexeme == "(" || str_lexeme == ")")
    lex = createLeftRightParenthesis(str_lexeme.c_str()[0]);
  else if (str_lexeme == "x")
    lex = createX();
  return lex;
}

void Model::lexemize() {
  if (!this->list_lex_expression_.empty())
    deleteLexemes(this->list_lex_expression_);
  std::regex lexeme_pattern(Model::kRegularMathExpression_);
  std::sregex_iterator it_lexemes(this->math_expression_.begin(),
                                  this->math_expression_.end(), lexeme_pattern);
  std::sregex_iterator end;
  std::size_t count_validation = 0;
  while (it_lexemes != end) {
    Lexeme *lex = createLexeme(it_lexemes->str());
    if (lex != nullptr) this->list_lex_expression_.push_back(lex);
    count_validation += it_lexemes->str().size();
    ++it_lexemes;
  }

  if (this->math_expression_.size() != count_validation) {
    throw Model::CalculationException(1);
  }
  searchUnaryOperator();
}

void Model::searchUnaryOperator() {
  Lexeme *prev_lexeme = nullptr;
  for (auto *lexeme : this->list_lex_expression_) {
    if (prev_lexeme == nullptr || prev_lexeme->type_ == 'o' ||
        prev_lexeme->type_ == 'u' || prev_lexeme->type_ == '(') {
      if (lexeme->o_ == '-' || lexeme->o_ == '+') {
        lexeme->type_ = 'u';
      }
    }
    prev_lexeme = lexeme;
  }
}

void Model::reversePolishNotation() {
  list_type list_lexemes = this->list_lex_expression_;
  list_type result_list_rpn;
  list_type trash_lexemes;
  std::stack<Lexeme *> stack;
  auto it_list_begin = list_lexemes.begin();
  auto it_list_end = list_lexemes.end();
  while (it_list_begin != it_list_end) {
    if ((*it_list_begin)->type_ == 'f') {
      auto it_lex_next = it_list_begin;
      if ((++it_lex_next) == it_list_end && (*(++it_lex_next))->type_ != '(')
        throw Model::CalculationException(1);
      stack.push(*(--it_lex_next));
    } else if ((*it_list_begin)->type_ == 'u') {
      stack.push(*it_list_begin);
    } else if ((*it_list_begin)->type_ == 'o') {
      Lexeme *op1 = *it_list_begin;
      /*
       * Пока присутствует на вершине стека лексема-оператор (op2) чей приоритет
       * выше приоритета O1, либо при равенстве приоритетов op1 является
       * левоассоциативным: Перекладываем op2 из стека в выходную очередь.
       */
      // Переложить op2 из стека в выходную очередь:
      while (!stack.empty()) {
        Lexeme *op2 = stack.top();
        if ((op2->type_ != 'o' && op2->type_ != 'u') ||
            (op1->o_ == '^' && op2->o_ != '^') ||
            ((op1->o_ == '*' || op1->o_ == '/' || op1->o_ == 'm') &&
             (op2->o_ == '+' || op2->o_ == '-'))) {
          break;
        } else {
          result_list_rpn.push_back(op2);
          stack.pop();
        }
      }
      // Положить op1 в стек
      stack.push(op1);
    } else if ((*it_list_begin)->type_ == '(') {
      stack.push(*it_list_begin);
    } else if ((*it_list_begin)->type_ == ')') {
      /*
       * если токен закрывающая скобка, пока токен на вершине стека не
       * открывающая скобка переложить оператор из стека в выходную очередь;
       */
      bool open_bracket_found = false;
      while (!stack.empty()) {
        Lexeme *op2 = stack.top();
        if (op2->type_ != '(') {
          result_list_rpn.push_back(op2);
          stack.pop();
        } else {
          open_bracket_found = true;
          // Выкидываем открывающую скобку из стека
          trash_lexemes.push_back(op2);
          stack.pop();
          break;
        }
      }
      // Если не нашли открывающую скобку
      if (!open_bracket_found) throw Model::CalculationException(1);

      // Если на вершине стека - функция, надо переложить в список результат
      if (!stack.empty() && stack.top()->type_ == 'f') {
        result_list_rpn.push_back(stack.top());
        stack.pop();
      }
      trash_lexemes.push_back(*it_list_begin);
    } else {
      result_list_rpn.push_back(*it_list_begin);
    }
    ++it_list_begin;
  }
  // Если больше не осталось лексем на входе,
  // и если остались лексемы в стеке, надо их переложить
  // в список результат
  while (!stack.empty()) {
    Lexeme *op2 = stack.top();
    // только операторы и возможно функции должны оставаться в стеке
    if (op2->type_ == 'o' || op2->type_ == 'u' || op2->type_ == 'f') {
      result_list_rpn.push_back(op2);
      stack.pop();
    } else {
      throw Model::CalculationException(1);
    }
  }
  Model::deleteLexemes(trash_lexemes);
  this->list_lex_expression_ = std::move(result_list_rpn);
}

double Model::calculateExpressionRpn(const double &x) {
  std::stack<Lexeme *> stack;
  list_type trash_lexemes_res;
  int error = 0;
  for (auto *lexeme : this->list_lex_expression_) {
    if (error > 0) break;
    if (lexeme->type_ == 'v' || lexeme->type_ == 'x') {
      stack.push(lexeme);
    } else if (lexeme->type_ == 'o') {
      try {
        applyOperator(lexeme, stack, x);
        trash_lexemes_res.push_back(stack.top());
      } catch (Model::CalculationException &err) {
        error = err.getError();
      }
    } else if (lexeme->type_ == 'f' || lexeme->type_ == 'u') {
      try {
        applyFunction(lexeme, stack, x);
        trash_lexemes_res.push_back(stack.top());
      } catch (Model::CalculationException &err) {
        error = err.getError();
      }
    }
  }
  if (error > 0) {
    Model::deleteLexemes(trash_lexemes_res);
    throw Model::CalculationException(error);
  }
  Lexeme *op1 = stack.top();
  stack.pop();
  if (!stack.empty()) {
    Model::deleteLexemes(trash_lexemes_res);
    throw Model::CalculationException(2);
  }
  double result = op1->type_ == 'x' ? x : op1->v_;
  Model::deleteLexemes(trash_lexemes_res);
  return result;
}

void Model::applyFunction(const Lexeme *lex, std::stack<Lexeme *> &stack,
                          const double &x) {
  if (stack.empty()) throw CalculationException(2);
  Lexeme *op1 = stack.top();
  stack.pop();
  double v1 = op1->type_ == 'x' ? x : op1->v_;
  Lexeme *result = nullptr;
  if (lex->f_ == "sin") {
    result = createValue(std::sin(v1));
  } else if (lex->f_ == "cos") {
    result = createValue(std::cos(v1));
  } else if (lex->f_ == "tan") {
    result = createValue(std::tan(v1));
  } else if (lex->f_ == "asin") {
    result = createValue(std::asin(v1));
  } else if (lex->f_ == "acos") {
    result = createValue(std::acos(v1));
  } else if (lex->f_ == "atan") {
    result = createValue(std::atan(v1));
  } else if (lex->f_ == "sqrt") {
    if (v1 < 0) throw CalculationException(4);
    result = createValue(std::sqrt(v1));
  } else if (lex->f_ == "ln") {
    if (v1 < 0) throw CalculationException(4);
    result = createValue(std::log(v1));
  } else if (lex->f_ == "log") {
    if (v1 < 0) throw CalculationException(4);
    result = createValue(std::log10(v1));
  } else if (lex->type_ == 'u') {
    if (lex->o_ == '-') result = createValue(v1 * (-1));
    if (lex->o_ == '+') result = createValue(v1);
  }
  stack.push(result);
}

void Model::applyOperator(const Lexeme *lex, std::stack<Lexeme *> &stack,
                          const double &x) {
  if (stack.size() < 2) throw CalculationException(2);
  Lexeme *op2 = stack.top();
  stack.pop();
  Lexeme *op1 = stack.top();
  stack.pop();
  Lexeme *result = nullptr;
  double v1 = op1->type_ == 'x' ? x : op1->v_;
  double v2 = op2->type_ == 'x' ? x : op2->v_;
  if (lex->o_ == '+') {
    result = createValue(v1 + v2);
  } else if (lex->o_ == '-') {
    result = createValue(v1 - v2);
  } else if (lex->o_ == '*') {
    result = createValue(v1 * v2);
  } else if (lex->o_ == '^') {
    result = createValue(std::pow(v1, v2));
  } else if (lex->o_ == '/') {
    if (v2 == 0) throw Model::CalculationException(3);
    result = createValue(v1 / v2);
  } else if (lex->o_ == 'm') {
    if (v2 == 0) throw Model::CalculationException(3);
    result = createValue(std::fmod(v1, v2));
  }
  stack.push(result);
}

CalculationResult Model::calculateExpression(const std::string &expression,
                                             const double &x) {
  this->math_expression_ = expression;
  CalculationResult result;
  try {
    if (this->math_expression_.size() == 0)
      throw Model::CalculationException(5);
    lexemize();
    reversePolishNotation();
    result.result_ = calculateExpressionRpn(x);
    result.error_ = 0;
  } catch (Model::CalculationException &err) {
    result.error_ = err.getError();
  }
  return result;
}

GraphResult Model::calculateExpressionGraph(const double &xBegin,
                                            const double &xEnd,
                                            const std::string &expression,
                                            const std::size_t &points) {
  this->math_expression_ = expression;
  GraphResult result;
  result.error_ = 0;
  try {
    if (this->math_expression_.size() == 0)
      throw Model::CalculationException(5);
    lexemize();
    reversePolishNotation();
    double width_x = xEnd - xBegin;
    double step = width_x / (points - 1);
    double x = xBegin;
    double y = 0;
    for (std::size_t i = 0; i < points; i++) {
      try {
        y = calculateExpressionRpn(x);
      } catch (Model::CalculationException &err) {
        if (err.getError() == 4 || err.getError() == 3) {
          y = 0.0 / 0.0;
        } else {
          result.error_ = err.getError();
          break;
        }
      }
      result.x_.push_back(x);
      result.y_.push_back(y);
      x += step;
    }
  } catch (Model::CalculationException &err) {
    result.error_ = err.getError();
  }
  return result;
}

}  // namespace s21
