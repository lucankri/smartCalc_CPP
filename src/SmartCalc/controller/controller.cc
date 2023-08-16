#include "controller.h"

namespace s21 {

Controller::Controller(Model *model) : model_(model){};

CalculationResult Controller::calculateExpression(const std::string &expression,
                                                  const double &x) {
  CalculationResult result = this->model_->calculateExpression(expression, x);
  return result;
}

GraphResult Controller::calculateGraph(const double &xBegin, const double &xEnd,
                                       const std::string &expression,
                                       const std::size_t &points) {
  GraphResult result =
      this->model_->calculateExpressionGraph(xBegin, xEnd, expression, points);
  return result;
}

}  // namespace s21
