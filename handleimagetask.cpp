
#include "handleimagetask.h"

HandleImageTask::HandleImageTask(Image* im,QImage* p,QObject* parent) :QObject{parent}, i((im)), prevImg(p)
{

}

void HandleImageTask::run(){
    i->compareToPreviousImage(prevImg);
    emit finishedHandling();
}
