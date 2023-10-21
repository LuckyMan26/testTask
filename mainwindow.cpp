
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    screen =  QGuiApplication::primaryScreen();

    layout = new QGridLayout();
    ui->centralwidget->setLayout(layout);
    button = new QPushButton("Click me");
    layout->addWidget(button,2,0);
    connect(button,&QPushButton::clicked,this,&MainWindow::takeScreenShot);

}
void MainWindow::takeScreenShot(){
    QString filePath = "E:/images/my_image.png";
    qDebug()<<filePath;
    QPixmap pixmap = screen->grabWindow(0);
    QImage image = pixmap.toImage();
    qDebug()<<image.save(filePath)<<"\n";
    qDebug() << "Saved\n";
}
MainWindow::~MainWindow()
{
    delete ui;
}


