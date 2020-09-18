#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GraphDrawer.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setWindowTitle("GraphDrawer");
  scene = new graphics;
  ui->graphicsView->setScene(scene);
  ui->graphicsView->show();
  connect(ui->actionNode,&QAction::triggered,scene,&graphics::setNodeDrawMode);
  connect(ui->actionEdge,&QAction::triggered,scene,&graphics::setEdgeDrawMode);

}

MainWindow::~MainWindow()
{
  delete scene;
  delete ui;
}


