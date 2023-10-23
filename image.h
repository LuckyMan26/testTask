
#ifndef IMAGE_H
#define IMAGE_H

#include "db.h"
#include <QImage>

#include <QObject>


class Image :  public QObject
{
    Q_OBJECT
    QByteArray hashsum;
    double similarity;

    QImage* img;

    QByteArray calculateImageHash();

public:
    static db d;
    Image();
    Image(QImage& i, QObject* p=nullptr);
    Image(Image& i);
    void saveToDB();
    double compareToPreviousImage(QImage* img);
    void saveToDB() const;
    QPixmap getPixmap();

    QImage resize(int w, int h) const;
    QImage getImg() const;
    double getSimilarity() const;
    void handleImage(QImage* prevImg);
    void setSimilarity(double);
    void setImg(QImage);
signals:
    void finishedSavingToDB(void);

};

#endif // IMAGE_H
