
#include "image.h"
#include "qpixmap.h"
#include "QDebug"
#include <QRgb>
#include <QSql>
#include <QBuffer>
#include <QCryptographicHash>
#include <QPainter>

db Image::d = db();
Image::Image(QImage& i,QObject* p) : QObject{p}
{
    img = new QImage(i);
    hashsum = calculateImageHash();

}
QByteArray Image::calculateImageHash(){
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    img->save(&buffer, "PNG");
    buffer.close();


    QByteArray hash = QCryptographicHash::hash(imageData, QCryptographicHash::Md5);

    return hash.toHex();
}
QImage Image::getImg(){
    return (*img);
}
void Image::saveToDB() {
    d.saveToDB(*img,hashsum);
    emit finishedSavingToDB();
}

QPixmap Image::getPixmap(){
    QPixmap m = QPixmap::fromImage(*img);
    return m;
}
QImage Image::resize(int w,int h){

    QImage resizedImage(w, h, QImage::Format_ARGB32);

    QPainter painter(&resizedImage);

    painter.drawImage(0, 0, img->scaled(w, h));

    painter.end();
    return resizedImage;
}
double Image::compareToPreviousImage(){
    QString url = "E:/images/image_13_21_36.png";

    QPixmap image(url);
    QImage* left = new QImage(image.toImage());

    int w=std::min(left->width(), img->width());
    int h=std::min(left->height(),img->height());
    QImage* result = new QImage(QSize(w,h),QImage::Format_ARGB32_Premultiplied);

   long double mse = 0;
  for(int i=0;i<h;i++){
        QRgb *rgbLeft=(QRgb*)left->constScanLine(i);
        QRgb *rgbRigth=(QRgb*)img->constScanLine(i);
        QRgb *rgbResult=(QRgb*)result->constScanLine(i);

    for(int j=0;j<w;j++){

        rgbResult[j] = rgbLeft[j]-rgbRigth[j];

        double res = rgbResult[j]*rgbResult[j];

        mse+=(res);
    }
  }

  long double max_mse = (((w*h))*255*255);

  mse = mse/(w*h);
  long double nmse = 100*(mse/max_mse);

  long double similarity_percentage = 100-nmse;
  result->save("E:/images/result.png");

  return similarity_percentage;
}
