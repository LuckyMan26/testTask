
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    layout = new QGridLayout();
    ui->centralwidget->setLayout(layout);
    button = new QPushButton("Click me");
    layout->addWidget(button,2,0);
    connect(button,&QPushButton::clicked,this,&MainWindow::takeScreenShot);

}
void MainWindow::takeScreenShot(){
    qDebug() << "Clicked\n";
}
MainWindow::~MainWindow()
{
    delete ui;
}


