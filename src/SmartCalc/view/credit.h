#ifndef CREDIT_H
#define CREDIT_H
#include <QDialog>

#include "../controller/controller.h"
#define CREDIT_DEFAULT_STYLE_EDIT \
  "QLineEdit { color: white;\
        background-color: rgb(30, 30, 30);\
        border-radius: 10px; border: 1px solid rgb(0, 0, 0);}\
    QLineEdit:focus {border: 1px solid rgb(0, 200, 255);\
        background-color: rgb(0, 20, 26);}"
#define CREDIT_ERROR_STYLE_EDIT \
  "QLineEdit {\
    background-color: rgb(60, 0, 0); color: white; border-radius: 5px; border: 1 solid red;}"
#define CREDIT_DEFAULT_STYLE_BAR \
  "QMainWindow {background-color: black;}\
    QScrollArea {border: none;}\
    QScrollBar:Vertical {\
        background-color: rgb(50, 50, 50); border: none;\
        width: 10px; border-radius: 5px; margin: 0;}\
    QScrollBar::handle:vertical {\
        background-color: rgb(80, 80, 122);\
        min-height: 30px; border-radius: 5px;}\
    QScrollBar::handle:vertical:hover{	\
        background-color: rgb(255, 0, 127);}\
    QScrollBar::handle:vertical:pressed {\
        background-color: rgb(185, 0, 92);}\
    QScrollBar::sub-line:vertical {\
        border: none;\
        background-color: rgb(59, 59, 90);\
        height: 15px;\
        border-top-left-radius: 5px;\
        border-top-right-radius: 5px;\
        subcontrol-position: top;}\
    QScrollBar::sub-line:vertical:hover {\
        background-color: rgb(255, 0, 127);}\
    QScrollBar::sub-line:vertical:pressed {\
        background-color: rgb(185, 0, 92);}\
    QScrollBar::add-line:vertical {\
        border: none;\
        background-color: rgb(59, 59, 90);\
        height: 15px;\
        border-bottom-left-radius: 5px;\
        border-bottom-right-radius: 5px;\
        subcontrol-position: bottom;}\
    QScrollBar::add-line:vertical:hover {\
        background-color: rgb(255, 0, 127);}\
    QScrollBar::add-line:vertical:pressed {\
        background-color: rgb(185, 0, 92);}\
    QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {\
        background: none;}\
    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\
        background: none;}\
    QScrollBar:Horizontal {\
        background-color: rgb(50, 50, 50); border: none;\
        height: 10px; border-radius: 5px; margin: 0;}\
    QScrollBar::handle:horizontal {\
        background-color: rgb(80, 80, 122);\
        min-width: 30px; border-radius: 5px;}\
    QScrollBar::handle:horizontal:hover{	\
        background-color: rgb(255, 0, 127);}\
    QScrollBar::handle:horizontal:pressed {\
        background-color: rgb(185, 0, 92);}\
    QScrollBar::sub-line:horizontal {\
        border: none;\
        background-color: rgb(59, 59, 90);\
        width: 15px;\
        border-top-left-radius: 5px;\
        border-bottom-left-radius: 5px;\
        subcontrol-position: left;}\
    QScrollBar::sub-line:horizontal:hover {\
        background-color: rgb(255, 0, 127);}\
    QScrollBar::sub-line:horizontal:pressed {\
        background-color: rgb(185, 0, 92);}\
    QScrollBar::add-line:horizontal {\
        border: none;\
        background-color: rgb(59, 59, 90);\
        width: 15px;\
        border-top-right-radius: 5px;\
        border-bottom-right-radius: 5px;\
        subcontrol-position: right;}\
    QScrollBar::add-line:horizontal:hover {\
        background-color: rgb(255, 0, 127);}\
    QScrollBar::add-line:horizontal:pressed {\
        background-color: rgb(185, 0, 92);}\
    QScrollBar::up-arrow:horizontal, QScrollBar::down-arrow:horizontal {\
        background: none;}\
    QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {\
        background: none;}"

namespace s21 {
namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(Controller *controller, QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_button_calculate_clicked();

 private:
  void differentiatedCredit(const QString &amount, const QString &term,
                            const QString &rate);
  void annuityCredit(const QString &amount, const QString &term,
                     const QString &rate);
  void setTextLabel(bool flagError, const QString &total,
                    const QString &overpayment, const QString &monthly_payment);
  Ui::Credit *ui;
  Controller *credit_controller_;
};
}  // namespace s21

#endif  // CREDIT_H
