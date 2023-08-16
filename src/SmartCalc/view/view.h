#ifndef VIEW_H
#define VIEW_H
#include <QMainWindow>
#include <QResizeEvent>
#include <QScrollBar>

#include "../controller/controller.h"
#include "credit.h"
#include "graph.h"
#include "inputx.h"
#define DEFAULT_STYLE_EDIT \
  "QLineEdit {\
        background-color: rgb(30, 30, 30); color: white; border-radius: 5px;\
        border: 1px solid rgb(0, 0, 0);}\
    QLineEdit:focus {border: 1px solid rgb(0, 200, 255); background-color: rgb(0, 20, 26);}"
#define ERROR_STYLE_EDIT \
  "QLineEdit {\
    background-color: rgb(60, 0, 0); color: white; border-radius: 5px; border: 1 solid red;}"
#define DEFAULT_STYLE_BAR \
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
QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(Controller* controller, QWidget* parent = nullptr);
  ~View();

 protected:
  void resizeEvent(QResizeEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;

 private slots:
  void moveScrollBarToBottom(int min, int max);
  void on_button_clear_history_clicked();
  void on_button_equals_clicked();
  void printNumber();
  void printOperator();
  void printFunction();
  void printParenthesis();
  void on_button_backspace_clicked();
  void on_button_delete_expression_clicked();
  void on_button_show_graph_clicked();
  void on_button_credit_clicked();

 private:
  void updateFont();
  int m_previousHeight_;
  Ui::View* ui;
  Inputx* input_x_;
  Controller* calc_controller_;
  Graph* graph_;
  Credit* credit;
};
}  // namespace s21
#endif  // VIEW_H
