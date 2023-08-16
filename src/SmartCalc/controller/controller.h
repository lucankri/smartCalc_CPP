#ifndef SMARTCALC_CONTROLLER_H
#define SMARTCALC_CONTROLLER_H
#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  Controller(Model *model);
  CalculationResult calculateExpression(const std::string &expression,
                                        const double &x);
  GraphResult calculateGraph(const double &xBegin, const double &xEnd,
                             const std::string &expression,
                             const std::size_t &points);

 private:
  Model *model_;
};

}  // namespace s21

#endif  // SMARTCALC_CONTROLLER_H
