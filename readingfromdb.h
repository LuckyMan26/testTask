
#ifndef READINGFROMDB_H
#define READINGFROMDB_H


#include <QObject>
#include <QRunnable>
#include "image.h"

//This class which we put in QThreadPool (it reads element with ID=index and returns Image)
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

};

#endif // READINGFROMDB_H
