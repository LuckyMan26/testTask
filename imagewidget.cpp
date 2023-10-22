
#include "imagewidget.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include "imagewindow.h"

ImageWidget::ImageWidget(Image& i,QWidget *parent)
    : QWidget{parent}

{
    QImage img = i.getImg();
    image = new Image(img);

    label = new QLabel(this);
    imageLabel = new QLabel(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    label->setText("Similarity: 0.5");
    layout->addWidget(label);
    layout->addWidget(imageLabel);
    setLayout(layout);
    connect(this,&ImageWidget::clicked, this, &ImageWidget::toggleFullscreen);
    QImage tempImg = i.resize(250,250);

    setImage(tempImg);
}
void ImageWidget::setImage(const QImage& im) {

    QPixmap pixmap = QPixmap::fromImage(im);
    imageLabel->setPixmap(pixmap);

}
void ImageWidget::toggleFullscreen(){
    imageWindow* iW = new imageWindow(image->getImg(), nullptr);
    iW->show();
}
void ImageWidget::mousePressEvent ( QMouseEvent * event ){
    emit clicked();
}
