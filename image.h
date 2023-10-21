
#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include "db.h"



class Image
{
    QByteArray hashsum;
    double similarity;

    QImage* img;

    QByteArray calculateImageHash();
public:
    static db d;
    Image(QImage& i);
    void saveToDB();
    double compareToPreviousImage();
    void saveToDB() const;

};

#endif // IMAGE_H
