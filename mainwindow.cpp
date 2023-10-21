
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    layout = new QGridLayout();
    ui->centralwidget->setLayout(layout);


}

MainWindow::~MainWindow()
{
    delete ui;
}


