
#include "readingfromdb.h"
#include "image.h"
#include "db.h"
#include "qthread.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>

ReadingFromDb::ReadingFromDb(int index,QObject *parent)
    : QObject{parent},
    index(index)
{
    i = new Image();
}

void ReadingFromDb::run(){
    QString dbName = "my_db_" + QString::number((quint64)QThread::currentThread(), 16);
    QImage image;
    Image* img_ = new Image();
    {

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", dbName);
    database.setDatabaseName("E:/db/database.db");
    qDebug() << "Index: " << index << "\n";
    if(!database.open()){
        qDebug() << "database not open\n";
    }
    QSqlQuery query = QSqlQuery(database);
    query.prepare("SELECT image, similarity FROM images WHERE ID = :index");
    query.bindValue(":index", index);

    if (query.exec() && query.first()) {
        QByteArray imageData = query.value(0).toByteArray();
        double s = query.value(1).toDouble();

        if (image.loadFromData(imageData, "PNG")) {

            if(image.isNull()){
                qDebug() << "Null\n";
            }
            qDebug() <<"here\n";
            Image img = Image(image);
            img.setSimilarity(s);
            img_ = new Image(img);



        } else {
            qDebug() << "Failed to load image from data.";
        }
    } else {
        qDebug() << "Failed to retrieve image: " << query.lastError().text();
    }

    database.close();
    }
    qDebug() << "here 2\n";
    i = new Image(*img_);
    QSqlDatabase::removeDatabase(dbName);
    if(i!=nullptr){
    qDebug() << "i!=nullptr\n";
    }
    if(image.isNull()){
    qDebug() << "Null\n";
    }
    i->setImg(image);
    qDebug() << "emitting\n";
    emit finishedReading((i));

}

Image ReadingFromDb::getImage(){
    qDebug() << "Get Image\n";

    if(i==nullptr){
    qDebug() <<"nullptr\n";
    }
    if(i!=nullptr){
    qDebug() <<"not nullptr\n";
    }

    i->setSimilarity(0);
    qDebug() << "Similarity: " << i->getSimilarity() << "\n";
    return (*i);
}
