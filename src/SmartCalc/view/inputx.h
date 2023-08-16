#ifndef INPUTX_H
#define INPUTX_H

#include <QDialog>

namespace s21 {
namespace Ui {
class Inputx;
}

class Inputx : public QDialog {
  Q_OBJECT

 public:
  explicit Inputx(QWidget *parent = nullptr);
  ~Inputx();
  QString takeValue();

 private slots:
  void on_button_ok_clicked();

 private:
  Ui::Inputx *ui;
};
}  // namespace s21

#endif  // INPUTX_H
