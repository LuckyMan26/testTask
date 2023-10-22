
#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include "db.h"
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
    Image(QImage& i,QObject* p=nullptr);
    void saveToDB();
    double compareToPreviousImage(QImage* img);
    void saveToDB() const;
    QPixmap getPixmap();

    QImage resize(int w, int h);
    QImage getImg();
    double getSimilarity();
    void handleImage(QImage* prevImg);
signals:
    void finishedSavingToDB(void);

};

#endif // IMAGE_H
