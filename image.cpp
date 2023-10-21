
#include "image.h"
#include "qpixmap.h"
#include "QDebug"
#include <QRgb>
Image::Image()
{
    //img = new QImage(image);
    QString url = "E:/images/image_12_38_01.png";

    QPixmap im(url);
    img = new QImage(im.toImage());
    hashsum = 1;
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
            rgbLeft[j]->
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
