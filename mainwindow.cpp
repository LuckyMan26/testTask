
#include "mainwindow.h"
#include "ImageDownloader.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDateTime>
#include <QTimer>
#include "image.h"
#include <QLabel>
#include "imagewidget.h"
#include "handleimagetask.h"
#include <QThreadPool>
#include "readingfromdb.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)


{
    ui->setupUi(this);

    prevImage = new QImage();
    prevImage = nullptr;
    screen =  QGuiApplication::primaryScreen();
    filePath = "E:/images/";
    layout = new QGridLayout();
    ui->centralwidget->setLayout(layout);
    button = new QPushButton("Start");
    button->setStyleSheet("font-size: 20px; font-weight: bold;");


    button->setStyleSheet("background-color: green; color: white;");
    layout->addWidget(button,0,0, Qt::AlignTop);
    connect(button,&QPushButton::clicked,this,&MainWindow::takeScreenShot);
    timer = new QTimer(this);

    connect(timer,&QTimer::timeout,this,&MainWindow::takeScreenShot);
    timer->start(60000);
    cur_row = 0;
    cur_col = 1;
    readImagesFromDB();

}
void MainWindow::readImagesFromDB(){

    Image img;
    int num_max = img.d.getMaxId();
    int num_min = img.d.getMinId();

    for(int i=num_min;i <= num_max;i++){
        ReadingFromDb* task = new ReadingFromDb(i);
        connect(task, &ReadingFromDb::finishedReading, this, [this](const Image* img){
                qDebug() << "Hello from here\n";
                addImgToLayout(*img);

            });
        QThreadPool::globalInstance()->start(task);
    }

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


    HandleImageTask* task = new HandleImageTask(img,prevImage);
    connect(task, &HandleImageTask::finishedHandling, this, [img,this]{addImgToLayout(*img); img->saveToDB();},Qt::ConnectionType::QueuedConnection);

    QThreadPool::globalInstance()->start(task);
    prevImage = new QImage(image);

    connect(img, &QObject::destroyed,
            [] { qDebug() << "Sender got deleted!"; });
    connect(this, &QObject::destroyed,
            [] { qDebug() << "Receiver got deleted!"; });

    qDebug() << "Saved\n";
}
void MainWindow::addImgToLayout(const Image& i){

    qDebug() << "adding to layout\n";
    if(!i.getImg().isNull()){
        qDebug() << "not Null\n";
    }
    ImageWidget* w = new ImageWidget(i);
    layout->addWidget(w, cur_row, cur_col,cur_row,cur_col);

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


