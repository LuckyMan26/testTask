
#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>




class Image
{
    int hashsum;
    double similarity;

    QImage* img;
public:
    Image();
    void saveToDB();
    double compareToPreviousImage();

};

#endif // IMAGE_H
