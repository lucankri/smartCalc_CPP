#include "inputx.h"

#include "ui_inputx.h"

namespace s21 {
Inputx::Inputx(QWidget *parent) : QDialog(parent), ui(new Ui::Inputx) {
  ui->setupUi(this);
  setWindowTitle("Enter number x...");
}

Inputx::~Inputx() { delete ui; }

QString Inputx::takeValue() { return ui->edit_value->text(); }

void Inputx::on_button_ok_clicked() {
  bool ok;
  ui->edit_value->text().toDouble(&ok);
  if (!ok)
    ui->edit_value->setStyleSheet(
        "QLineEdit {\
                    background-color: rgb(70, 0, 0);\
                    color: white; border-radius: 10px; border: 1 solid red;}");
  else
    this->close();
}
}  // namespace s21
