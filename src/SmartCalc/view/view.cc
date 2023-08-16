#include "view.h"

#include <iostream>

#include "./ui_view.h"
namespace s21 {

View::View(Controller* controller, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::View), calc_controller_(controller) {
  ui->setupUi(this);
  setWindowTitle("Smart Calculator");
  connect(ui->scrollArea->verticalScrollBar(), SIGNAL(rangeChanged(int, int)),
          this, SLOT(moveScrollBarToBottom(int, int)));
  connect(ui->scrollArea->horizontalScrollBar(), SIGNAL(rangeChanged(int, int)),
          this, SLOT(moveScrollBarToBottom(int, int)));
  this->setStyleSheet(DEFAULT_STYLE_BAR);
  ui->mathExpression->setStyleSheet(DEFAULT_STYLE_EDIT);
  ui->resultHistory->setAlignment(Qt::AlignRight | Qt::AlignBottom);
  ui->showResult->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  ui->mathExpression->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  m_previousHeight_ = height();
  updateFont();

  connect(ui->button_x, SIGNAL(clicked()), this, SLOT(printNumber()));
  connect(ui->button_dot, SIGNAL(clicked()), this, SLOT(printNumber()));
  connect(ui->button_0, SIGNAL(clicked()), this, SLOT(printNumber()));
  connect(ui->button_1, SIGNAL(clicked()), this, SLOT(printNumber()));
  connect(ui->button_2, SIGNAL(clicked()), this, SLOT(printNumber()));
  connect(ui->button_3, SIGNAL(clicked()), this, SLOT(printNumber()));
  connect(ui->button_4, SIGNAL(clicked()), this, SLOT(printNumber()));
  connect(ui->button_5, SIGNAL(clicked()), this, SLOT(printNumber()));
  connect(ui->button_6, SIGNAL(clicked()), this, SLOT(printNumber()));
  connect(ui->button_7, SIGNAL(clicked()), this, SLOT(printNumber()));
  connect(ui->button_8, SIGNAL(clicked()), this, SLOT(printNumber()));
  connect(ui->button_9, SIGNAL(clicked()), this, SLOT(printNumber()));
  connect(ui->button_sum, SIGNAL(clicked()), this, SLOT(printOperator()));
  connect(ui->button_sub, SIGNAL(clicked()), this, SLOT(printOperator()));
  connect(ui->button_mod, SIGNAL(clicked()), this, SLOT(printOperator()));
  connect(ui->button_multiply, SIGNAL(clicked()), this, SLOT(printOperator()));
  connect(ui->button_division, SIGNAL(clicked()), this, SLOT(printOperator()));
  connect(ui->button_exp, SIGNAL(clicked()), this, SLOT(printOperator()));
  connect(ui->button_sin, SIGNAL(clicked()), this, SLOT(printFunction()));
  connect(ui->button_cos, SIGNAL(clicked()), this, SLOT(printFunction()));
  connect(ui->button_tan, SIGNAL(clicked()), this, SLOT(printFunction()));
  connect(ui->button_asin, SIGNAL(clicked()), this, SLOT(printFunction()));
  connect(ui->button_acos, SIGNAL(clicked()), this, SLOT(printFunction()));
  connect(ui->button_atan, SIGNAL(clicked()), this, SLOT(printFunction()));
  connect(ui->button_sqrt, SIGNAL(clicked()), this, SLOT(printFunction()));
  connect(ui->button_ln, SIGNAL(clicked()), this, SLOT(printFunction()));
  connect(ui->button_log, SIGNAL(clicked()), this, SLOT(printFunction()));
  connect(ui->button_parenthesis_left, SIGNAL(clicked()), this,
          SLOT(printParenthesis()));
  connect(ui->button_parenthesis_right, SIGNAL(clicked()), this,
          SLOT(printParenthesis()));
  ui->button_equals->setCheckable(true);
}

void View::moveScrollBarToBottom(int min, int max) {
  Q_UNUSED(min);
  ui->scrollArea->verticalScrollBar()->setValue(max);
  ui->scrollArea->horizontalScrollBar()->setValue(max);
}

View::~View() { delete ui; }

void View::resizeEvent(QResizeEvent* event) {
  int newHeight = event->size().height();
  if (newHeight != m_previousHeight_) {
    m_previousHeight_ = newHeight;
    updateFont();
  }
}

void View::updateFont() {
  QFont font = this->ui->resultHistory->font();
  if ((height() * 0.025) < 16) {
    font.setPointSizeF(height() * 0.025);
    this->ui->resultHistory->setFont(font);
    font = this->ui->showResult->font();
    font.setPointSizeF(height() * 0.035);
    this->ui->showResult->setFont(font);
    font = this->ui->mathExpression->font();
    font.setPointSizeF(height() * 0.035);
    this->ui->mathExpression->setFont(font);
  } else {
    font.setPointSizeF(640 * 0.025);
    this->ui->resultHistory->setFont(font);
    font = this->ui->showResult->font();
    font.setPointSizeF(640 * 0.035);
    this->ui->showResult->setFont(font);
    font = this->ui->mathExpression->font();
    font.setPointSizeF(640 * 0.035);
    this->ui->mathExpression->setFont(font);
  }
}

void View::keyPressEvent(QKeyEvent* event) {
  if (ui->mathExpression->hasFocus() &&
      (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter))
    on_button_equals_clicked();
}

void View::printNumber() {
  QPushButton* button = (QPushButton*)sender();
  if (ui->button_equals->isChecked()) {
    ui->mathExpression->setText("");
    ui->button_equals->setChecked(false);
  }
  ui->mathExpression->setText(ui->mathExpression->text() + button->text());
}

void View::printOperator() {
  QPushButton* button = (QPushButton*)sender();
  ui->mathExpression->setText(ui->mathExpression->text() + button->text());
  ui->button_equals->setChecked(false);
}

void View::printFunction() {
  QPushButton* button = (QPushButton*)sender();
  if (ui->button_equals->isChecked()) {
    ui->mathExpression->setText("");
    ui->button_equals->setChecked(false);
  }
  ui->mathExpression->setText(ui->mathExpression->text() + button->text() +
                              "(");
}

void View::printParenthesis() {
  QPushButton* button = (QPushButton*)sender();
  ui->mathExpression->setText(ui->mathExpression->text() + button->text());
  ui->button_equals->setChecked(false);
}

void View::on_button_clear_history_clicked() { ui->resultHistory->setText(""); }

void View::on_button_backspace_clicked() {
  QString str = ui->mathExpression->text();
  if (str.endsWith("sqrt(") || str.endsWith("atan(") || str.endsWith("acos(") ||
      str.endsWith("asin(")) {
    str.remove(str.size() - 5, 5);
    ui->mathExpression->setText(str);
  } else if (str.endsWith("sin(") || str.endsWith("cos(") ||
             str.endsWith("tan(") || str.endsWith("log(")) {
    str.remove(str.size() - 4, 4);
    ui->mathExpression->setText(str);
  } else if (str.endsWith("ln(") || str.endsWith("mod")) {
    str.remove(str.size() - 3, 3);
    ui->mathExpression->setText(str);
  } else {
    str.remove(str.size() - 1, 1);
    ui->mathExpression->setText(str);
  }
  ui->button_equals->setChecked(false);
}

void View::on_button_delete_expression_clicked() {
  ui->mathExpression->setStyleSheet(DEFAULT_STYLE_EDIT);
  ui->button_equals->setChecked(true);
  ui->mathExpression->setText("");
  ui->showResult->setText("");
}

void View::on_button_show_graph_clicked() {
  graph_ = new Graph(this->calc_controller_, this);
  graph_->setExpression(ui->mathExpression->text());
  graph_->show();
}

void View::on_button_equals_clicked() {
  QString q_str_math_expression = ui->mathExpression->text();
  double x = 0;
  QString str_x;
  if (q_str_math_expression.contains("x")) {
    this->input_x_ = new Inputx(this);
    this->input_x_->setModal(true);
    this->input_x_->exec();
    str_x = this->input_x_->takeValue();
    bool ok;
    x = str_x.toDouble(&ok);
    if (!ok) {
      ui->mathExpression->setStyleSheet(ERROR_STYLE_EDIT);
      ui->showResult->setStyleSheet(
          "QLabel {\
                                     color: red; background-color: black;}");
      ui->showResult->setText("Error! x: data entered incorrectly");
      return;
    }
  }
  std::string str_math_expression = q_str_math_expression.toStdString();
  s21::CalculationResult result =
      calc_controller_->calculateExpression(str_math_expression, x);
  if (result.getError() == 0) {
    ui->mathExpression->setStyleSheet(DEFAULT_STYLE_EDIT);
    ui->showResult->setStyleSheet(
        "QLabel {\
                                 color: green; background-color: black;}");
    QString value_result = QString::number(result.getResult(), 'g', 15);
    ui->showResult->setText(value_result);
    if (q_str_math_expression.contains("x"))
      ui->resultHistory->setText(
          ui->resultHistory->text() + "\n" + ui->mathExpression->text() +
          "\nx = " + str_x + "\n" + "= " + value_result + "\n" + "———————————");
    else
      ui->resultHistory->setText(ui->resultHistory->text() + "\n" +
                                 ui->mathExpression->text() + "\n" + "= " +
                                 value_result + "\n" + "———————————");
    ui->button_equals->setChecked(true);
  } else {
    ui->mathExpression->setStyleSheet(ERROR_STYLE_EDIT);
    ui->showResult->setStyleSheet(
        "QLabel {\
                                 color: red; background-color: black;}");
    if (result.getError() == 1) {
      ui->showResult->setText("Syntax error in the expression!");
    } else if (result.getError() == 2) {
      ui->showResult->setText("The expression is incorrectly composed!");
    } else if (result.getError() == 3) {
      ui->showResult->setText("Error! Division by 0!");
    } else if (result.getError() == 4) {
      ui->showResult->setText(
          "The sqrt, ln and log functions cannot be negative!");
    } else if (result.getError() == 5) {
      ui->showResult->setText("Empty!   :(");
    }
  }
}

void View::on_button_credit_clicked() {
  this->credit = new Credit(this->calc_controller_, this);
  this->credit->show();
}

}  // namespace s21
