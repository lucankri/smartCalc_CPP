#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QTimer>
#include <QVector>

#include "../controller/controller.h"

#define GRAPH_DEFAULT_STYLE_EDIT \
  "QLineEdit {\
        background-color: rgb(30, 30, 30);\
        color: white; border-radius: 10px;\
        border: 1px solid rgb(0, 0, 0);}\
    QLineEdit:focus {\
        border: 1px solid rgb(0, 200, 255);\
        background-color: rgb(0, 20, 26);}"

#define GRAPH_ERROR_STYLE_EDIT \
  "QLineEdit {\
        background-color: rgb(70, 0, 0);\
        color: white; border-radius: 10px;\
        border: 1 solid red;}"

namespace s21 {
namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(s21::Controller *controller, QWidget *parent = nullptr);
  ~Graph();
  void setExpression(const QString &expression);

 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void showEvent(QShowEvent *) override;

 private slots:
  void drawGraphicsAnimation();
  void on_button_show_clicked();

  void on_button_close_clicked();

 private:
  void drawGraph();
  Ui::Graph *ui;
  s21::Controller *graph_controller_;
  QTimer *timer_animation_;
  double xBegin_, xEnd_, yBegin_, yEnd_;
  QVector<double> x_, y_;
  QVector<double> x_animation_, y_animation_;
  QString expression_;
};
}  // namespace s21
#endif  // GRAPH_H
