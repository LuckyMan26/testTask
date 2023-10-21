
#include "image.h"
#include "qpixmap.h"

Image::Image()
{
    //img = new QImage(image);
    QString url = "E:/images/image_12_38_01.png";

    QPixmap im(url);
    img = new QImage(im.toImage());
    hashsum = 1;
}

double Image::compareToPreviousImage(){
    QString url = "E:/images/image_12_38_01.png";

    QPixmap image(url);
    QImage* left = new QImage(image.toImage());

    int w=std::min(left->width(), img->width());
    int h=std::min(left->height(),img->height());
    QImage* result = new QImage(QSize(w,h),QImage::Format_ARGB32_Premultiplied);

    double mse = 0;
  for(int i=0;i<h;i++){
        QRgb *rgbLeft=(QRgb*)left->constScanLine(i);
        QRgb *rgbRigth=(QRgb*)img->constScanLine(i);
        QRgb *rgbResult=(QRgb*)result->constScanLine(i);
    for(int j=0;j<w;j++){
        rgbResult[j] = rgbLeft[j]-rgbRigth[j];
        mse+=rgbResult[j]*rgbResult[j];
    }
  }
  mse = mse/(w*h);
  double similarity_percentage = 100.0 - (mse * 100.0);
  result->save("E:/images/result.png");

  return similarity_percentage;
}
