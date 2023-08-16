#include "graph.h"

#include "ui_graph.h"

namespace s21 {

Graph::Graph(s21::Controller *controller, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Graph),
      graph_controller_(controller),
      xBegin_(-10),
      xEnd_(10),
      yBegin_(-10),
      yEnd_(10),
      timer_animation_(new QTimer(this)) {
  ui->setupUi(this);
  setWindowTitle("Graph");
  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(50, 50, 50));
  plotGradient.setColorAt(1, QColor(30, 30, 30));
  ui->widget->setBackground(plotGradient);
  ui->widget->xAxis->setBasePen(QPen(Qt::blue, 1));
  ui->widget->yAxis->setBasePen(QPen(Qt::blue, 1));
  ui->widget->xAxis->setTickLabelColor(Qt::white);
  ui->widget->yAxis->setTickLabelColor(Qt::white);
  ui->widget->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->widget->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->widget->xAxis->ticker()->setTickCount(10);
  ui->widget->yAxis->ticker()->setTickCount(10);
  ui->widget->xAxis->setTickPen(QPen(Qt::red, 1));
  ui->widget->yAxis->setTickPen(QPen(Qt::red, 1));
  ui->widget->xAxis->grid()->setPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  ui->widget->yAxis->grid()->setPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->expressionShow->setWordWrap(true);
  ui->edit_xBegin->setText(QString::number(this->xBegin_));
  ui->edit_yBegin->setText(QString::number(this->yBegin_));
  ui->edit_xEnd->setText(QString::number(this->xEnd_));
  ui->edit_yEnd->setText(QString::number(this->yEnd_));
  ui->widget->addGraph();
  connect(this->timer_animation_, SIGNAL(timeout()), this,
          SLOT(drawGraphicsAnimation()));
}

void Graph::showEvent(QShowEvent *) { drawGraph(); }

Graph::~Graph() { delete ui; }

void Graph::setExpression(const QString &expression) {
  ui->mathExpression->setText(expression);
  ui->expressionShow->setText(expression);
}

void Graph::keyPressEvent(QKeyEvent *event) {
  if ((ui->mathExpression->hasFocus() || ui->edit_xBegin->hasFocus() ||
       ui->edit_xEnd->hasFocus() || ui->edit_yBegin->hasFocus() ||
       ui->edit_yEnd->hasFocus()) &&
      (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter))
    drawGraph();
}

void Graph::drawGraphicsAnimation() {
  if (this->x_.empty()) {
    this->x_animation_.clear();
    this->y_animation_.clear();
    this->x_.clear();
    this->y_.clear();
    this->timer_animation_->stop();
  } else {
    x_animation_.push_back(this->x_.front());
    y_animation_.push_back(this->y_.front());
    this->x_.pop_front();
    this->y_.pop_front();
    ui->widget->graph(0)->setData(this->x_animation_, this->y_animation_);
    ui->widget->replot();
  }
}

void Graph::drawGraph() {
  this->expression_ = ui->mathExpression->text();
  bool ok_xBegin, ok_yBegin, ok_xEnd, ok_yEnd;
  this->xBegin_ = ui->edit_xBegin->text().toDouble(&ok_xBegin);
  this->yBegin_ = ui->edit_yBegin->text().toDouble(&ok_yBegin);
  this->xEnd_ = ui->edit_xEnd->text().toDouble(&ok_xEnd);
  this->yEnd_ = ui->edit_yEnd->text().toDouble(&ok_yEnd);
  if (!ok_xBegin || !ok_yBegin || !ok_xEnd || !ok_yEnd) {
    if (!ok_xBegin) {
      ui->edit_xBegin->setStyleSheet(GRAPH_ERROR_STYLE_EDIT);
      ui->edit_xBegin->setFocus();
    } else {
      ui->edit_xBegin->setStyleSheet(GRAPH_DEFAULT_STYLE_EDIT);
    }
    if (!ok_yBegin) {
      ui->edit_yBegin->setStyleSheet(GRAPH_ERROR_STYLE_EDIT);
      ui->edit_yBegin->setFocus();
    } else {
      ui->edit_yBegin->setStyleSheet(GRAPH_DEFAULT_STYLE_EDIT);
    }
    if (!ok_xEnd) {
      ui->edit_xEnd->setStyleSheet(GRAPH_ERROR_STYLE_EDIT);
      ui->edit_xEnd->setFocus();
    } else {
      ui->edit_xEnd->setStyleSheet(GRAPH_DEFAULT_STYLE_EDIT);
    }
    if (!ok_yEnd) {
      ui->edit_yEnd->setStyleSheet(GRAPH_ERROR_STYLE_EDIT);
      ui->edit_yEnd->setFocus();
    } else {
      ui->edit_yEnd->setStyleSheet(GRAPH_DEFAULT_STYLE_EDIT);
    }
  } else {
    ui->edit_xBegin->setStyleSheet(GRAPH_DEFAULT_STYLE_EDIT);
    ui->edit_yBegin->setStyleSheet(GRAPH_DEFAULT_STYLE_EDIT);
    ui->edit_xEnd->setStyleSheet(GRAPH_DEFAULT_STYLE_EDIT);
    ui->edit_yEnd->setStyleSheet(GRAPH_DEFAULT_STYLE_EDIT);
    ui->widget->xAxis->setRange(this->xBegin_, this->xEnd_);
    ui->widget->yAxis->setRange(this->yBegin_, this->yEnd_);
    std::size_t pixel_x = (std::size_t)ui->widget->axisRect()->width();
    s21::GraphResult result = this->graph_controller_->calculateGraph(
        this->xBegin_, this->xEnd_, this->expression_.toStdString(), pixel_x);
    if (result.getError() == 0) {
      ui->expressionShow->setStyleSheet("QLabel {color: green;}");
      ui->mathExpression->setStyleSheet(GRAPH_DEFAULT_STYLE_EDIT);
      ui->expressionShow->setText(this->expression_);
      std::vector<double> temp_x = result.getX();
      std::vector<double> temp_y = result.getY();
      this->x_ = QVector<double>(temp_x.begin(), temp_x.end());
      this->y_ = QVector<double>(temp_y.begin(), temp_y.end());
      ui->widget->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
      ui->widget->graph(0)->setScatterStyle(
          QCPScatterStyle(QCPScatterStyle::ScatterShape::ssDisc, 2));
      ui->widget->graph(0)->setPen(QPen(Qt::red));
      this->x_animation_.clear();
      this->y_animation_.clear();
      this->timer_animation_->start(1);
    } else if (result.getError() == 1) {
      ui->expressionShow->setStyleSheet("QLabel {color: red;}");
      ui->mathExpression->setStyleSheet(GRAPH_ERROR_STYLE_EDIT);
      ui->expressionShow->setText("Syntax error in the expression!");
    } else if (result.getError() == 2) {
      ui->expressionShow->setStyleSheet("QLabel {color: red;}");
      ui->mathExpression->setStyleSheet(GRAPH_ERROR_STYLE_EDIT);
      ui->expressionShow->setText("The expression is incorrectly composed!");
    } else if (result.getError() == 5) {
      ui->expressionShow->setStyleSheet("QLabel {color: red;}");
      ui->mathExpression->setStyleSheet(GRAPH_ERROR_STYLE_EDIT);
      ui->expressionShow->setText("Empty!   :(");
    }
  }
}

void Graph::on_button_show_clicked() { drawGraph(); }

void Graph::on_button_close_clicked() { this->close(); }

}  // namespace s21
