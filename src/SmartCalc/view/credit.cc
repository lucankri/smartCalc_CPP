#include "credit.h"

#include "ui_credit.h"

namespace s21 {

Credit::Credit(Controller *controller, QWidget *parent)
    : QDialog(parent), ui(new Ui::Credit), credit_controller_(controller) {
  ui->setupUi(this);
  setWindowTitle("Credit calculator");
  this->setStyleSheet(CREDIT_DEFAULT_STYLE_BAR);
}

Credit::~Credit() { delete ui; }

void Credit::on_button_calculate_clicked() {
  bool ok_amount, ok_term, ok_rate;
  QString amount = ui->edit_total->text();
  QString term = ui->edit_term->text();
  QString rate = ui->edit_interest->text();
  amount.toDouble(&ok_amount);
  term.toInt(&ok_term);
  rate.toDouble(&ok_rate);
  if (!ok_amount || !ok_term || !ok_rate) {
    if (!ok_amount) {
      ui->edit_total->setStyleSheet(CREDIT_ERROR_STYLE_EDIT);
    } else {
      ui->edit_total->setStyleSheet(CREDIT_DEFAULT_STYLE_EDIT);
    }
    if (!ok_term) {
      ui->edit_term->setStyleSheet(CREDIT_ERROR_STYLE_EDIT);
    } else {
      ui->edit_term->setStyleSheet(CREDIT_DEFAULT_STYLE_EDIT);
    }
    if (!ok_rate) {
      ui->edit_interest->setStyleSheet(CREDIT_ERROR_STYLE_EDIT);
    } else {
      ui->edit_interest->setStyleSheet(CREDIT_DEFAULT_STYLE_EDIT);
    }
    setTextLabel(true, "", "", "");
    return;
  }
  ui->edit_total->setStyleSheet(CREDIT_DEFAULT_STYLE_EDIT);
  ui->edit_term->setStyleSheet(CREDIT_DEFAULT_STYLE_EDIT);
  ui->edit_interest->setStyleSheet(CREDIT_DEFAULT_STYLE_EDIT);
  if (ui->radio_annuity->isChecked()) {
    annuityCredit(amount, term, rate);
  } else {
    differentiatedCredit(amount, term, rate);
  }
}

void Credit::differentiatedCredit(const QString &amount, const QString &term,
                                  const QString &rate) {
  QString result_monthly_payment, result_overpayment, result_total_payment;
  QString credit_expression = amount + "/" + term;
  CalculationResult result = this->credit_controller_->calculateExpression(
      credit_expression.toStdString(), 0);
  if (result.getError() != 0) {
    setTextLabel(true, "", "", "");
    return;
  }
  QString principal_payment = QString::number(result.getResult(), 'f', 2);
  int term_v = term.toInt();
  double total_paid = 0;
  for (int i = 0; i < term_v; i++) {
    credit_expression = amount + "/" + term + "+(" + amount + "-(" +
                        principal_payment + "*" + QString::number(i, 'g', 20) +
                        "))*(" + rate + "/100)/12";
    result = this->credit_controller_->calculateExpression(
        credit_expression.toStdString(), 0);
    if (result.getError() != 0) {
      setTextLabel(true, "", "", "");
      return;
    }
    total_paid += result.getResult();
    result_monthly_payment += QString::number(i + 1, 'g', 20) + ": " +
                              QString::number(result.getResult(), 'f', 2) +
                              "\n";
  }
  setTextLabel(false, QString::number(total_paid, 'f', 2),
               QString::number(total_paid - amount.toDouble(), 'f', 2),
               result_monthly_payment);
}

void Credit::annuityCredit(const QString &amount, const QString &term,
                           const QString &rate) {
  QString result_monthly_payment, result_overpayment, result_total_payment;
  QString credit_expression = "(" + amount + "*" + rate + "/(12*100))/(1-(1+" +
                              rate + "/(12*100))^-" + term + ")";
  CalculationResult result = this->credit_controller_->calculateExpression(
      credit_expression.toStdString(), 0);
  if (result.getError() != 0) {
    setTextLabel(true, "", "", "");
    return;
  }
  result_monthly_payment = QString::number(result.getResult(), 'f', 2);
  credit_expression = result_monthly_payment + "*" + term;
  result = this->credit_controller_->calculateExpression(
      credit_expression.toStdString(), 0);
  if (result.getError() != 0) {
    setTextLabel(true, "", "", "");
    return;
  }
  result_total_payment = QString::number(result.getResult(), 'f', 2);
  credit_expression = result_total_payment + "-" + amount;
  result = this->credit_controller_->calculateExpression(
      credit_expression.toStdString(), 0);
  if (result.getError() != 0) {
    setTextLabel(true, "", "", "");
    return;
  }
  result_overpayment = QString::number(result.getResult(), 'f', 2);
  setTextLabel(false, result_total_payment, result_overpayment,
               result_monthly_payment);
}

void Credit::setTextLabel(bool flagError, const QString &total,
                          const QString &overpayment,
                          const QString &monthly_payment) {
  if (flagError) {
    ui->label_calculation_result->setText("Error!");
    ui->label_total_payment->setText("");
    ui->label_overpayment_loan->setText("");
    ui->label_monthly_payment->setText("");
    ui->label_total_payment_result->setText(total);
    ui->label_overpayment_result->setText(overpayment);
    ui->label_monthly_payment_result->setText(monthly_payment);
  } else {
    ui->label_calculation_result->setText("Calculation result");
    ui->label_total_payment->setText("Total payment:");
    ui->label_overpayment_loan->setText("Overpayment:");
    ui->label_monthly_payment->setText("Monthly payment:");
    ui->label_total_payment_result->setText(total);
    ui->label_overpayment_result->setText(overpayment);
    ui->label_monthly_payment_result->setText(monthly_payment);
  }
}

}  // namespace s21
