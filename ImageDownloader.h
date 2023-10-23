
#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H
#include "qobject.h"
#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include "image.h"
#include "qsqlerror.h"

class ImageDownloader : public QObject
{
    Q_OBJECT
public:
    Image* i;
signals:
    void finished();
public slots:
    void downloadImages()
    {
        /*QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("your_database_file.db");

        if (!db.open()) {
            qDebug() << "Database not open!";
            return;
        }

        QSqlQuery query;
        query.prepare("SELECT image, similarity FROM images WHERE ID = :index");
        query.bindValue(":index", 2);
        if (query.exec() && query.first()) {
            QByteArray imageData = query.value(0).toByteArray();
            double s = query.value(1).toDouble();
            QImage image;
            if (image.loadFromData(imageData,"PNG")) {
                Image img = Image(image);
                img.setSimilarty(s);
                i = new Image(img);

            } else {
                qDebug() << "Failed to load image from data.";
            }
        } else {
            qDebug() << "Failed to retrieve image:1 " << query.lastError().text();
        }

        db.close();*/
        emit finished();
    }
};
#endif // IMAGEDOWNLOADER_H
