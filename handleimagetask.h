
#ifndef HANDLEIMAGETASK_H
#define HANDLEIMAGETASK_H

#include <QRunnable>
#include "image.h"
#include <QObject>
//This class which we put in QThreadPool (it saves element in DB)
class HandleImageTask : public QObject, public QRunnable
{
    Q_OBJECT
    Image* i;
    QImage* prevImg;
public:
    HandleImageTask(Image* im,QImage* p=nullptr,QObject* parent=nullptr);
    void run() override;
signals:
    void finishedHandling();
};

#endif // HANDLEIMAGETASK_H
