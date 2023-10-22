
#include "imagewidget.h"
#include <QVBoxLayout>
#include <QMouseEvent>

ImageWidget::ImageWidget(QWidget *parent)
    : QWidget{parent}
{
    label = new QLabel(this);
    imageLabel = new QLabel(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    label->setText("Similarity: 0.5");
    layout->addWidget(label);
    layout->addWidget(imageLabel);
    setLayout(layout);
    connect(this,&ImageWidget::clicked, this, &ImageWidget::toggleFullscreen);
}
void ImageWidget::setImage(const QImage& im) {
    image = im;
    QPixmap pixmap = QPixmap::fromImage(im);
    imageLabel->setPixmap(pixmap);

}
void ImageWidget::toggleFullscreen(){
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}
void ImageWidget::mousePressEvent ( QMouseEvent * event ){
    emit clicked();
}
