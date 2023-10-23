
#ifndef READINGFROMDB_H
#define READINGFROMDB_H


#include <QObject>
#include <QRunnable>
#include "image.h"


class ReadingFromDb : public QObject, public QRunnable
{
    Q_OBJECT
    long long index;
    Image* i;
public:
    explicit ReadingFromDb(int index,QObject *parent = nullptr);
    void run() override;
    Image getImage();
signals:
    void finishedReading(const Image*);
    void imageLoaded(Image&);
};

#endif // READINGFROMDB_H
