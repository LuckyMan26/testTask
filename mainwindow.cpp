
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDateTime>
#include <QTimer>
#include "image.h"
#include <QLabel>
#include "t.h"
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
    cur_row = 0;
    cur_col = 0;


}
void MainWindow::takeScreenShot(){

    QDateTime currentDateTime = QDateTime::currentDateTime();


    QTime currentTime = currentDateTime.time();
    QString fileFullPath = filePath + "image_" + currentTime.toString("hh_mm_ss") +".png";
    qDebug()<<fileFullPath;
    QPixmap pixmap = screen->grabWindow(0);
    QImage image = pixmap.toImage();
    qDebug()<<image.save(fileFullPath)<<"\n";
    Image* img = new Image(image, this);

    connect(img, &Image::finishedSavingToDB, this, [img,this]{addImgToLayout(*img); });
    img->saveToDB();
    connect(img, &QObject::destroyed,
            [] { qDebug() << "Sender got deleted!"; });
    connect(this, &QObject::destroyed,
            [] { qDebug() << "Receiver got deleted!"; });

    qDebug() << "Saved\n";
}
void MainWindow::addImgToLayout(Image& i){
    qDebug() << "adding to layout\n";
    QImage imgTemp = i.resize(500,500);
    Image* resizedImage = new Image(imgTemp);
    QLabel *imageLabel = new QLabel(this);

    QPixmap imagePixmap = resizedImage->getPixmap();

    imageLabel->setPixmap(imagePixmap);

    layout->addWidget(imageLabel, cur_row, cur_col);

    cur_col++;
    if(cur_col > 5){
        cur_col = 0;
        cur_row++;
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}


