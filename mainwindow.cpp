
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDateTime>
#include <QTimer>
#include "image.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    screen =  QGuiApplication::primaryScreen();
    filePath = "E:/images/";
    layout = new QGridLayout();
    ui->centralwidget->setLayout(layout);
    button = new QPushButton("Click me");
    layout->addWidget(button,2,0);
    connect(button,&QPushButton::clicked,this,&MainWindow::takeScreenShot);
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::takeScreenShot);
    timer->start(60000);


}
void MainWindow::takeScreenShot(){
    QDateTime currentDateTime = QDateTime::currentDateTime();


    QTime currentTime = currentDateTime.time();
    QString fileFullPath = filePath + "image_" + currentTime.toString("hh_mm_ss") +".png";
    qDebug()<<fileFullPath;
    QPixmap pixmap = screen->grabWindow(0);
    QImage image = pixmap.toImage();
    qDebug()<<image.save(fileFullPath)<<"\n";
    Image* img = new Image(image);

    qDebug() << "Saved\n";
}
MainWindow::~MainWindow()
{
    delete ui;
}


