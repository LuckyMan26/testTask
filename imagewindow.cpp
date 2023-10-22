
#include "imagewindow.h"

imageWindow::imageWindow(const QImage& image,QWidget *parent)
    : QMainWindow{parent}
{
    imageLabel = new QLabel(this);
    setCentralWidget(imageLabel);

    QPixmap pixmap = QPixmap::fromImage(image);
    imageLabel->setPixmap(pixmap);
    showMaximized();
}

