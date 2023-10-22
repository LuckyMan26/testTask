
#include "db.h"
#include <QDebug>
#include <QFile>
#include <QBuffer>
#include <QSqlQuery>
#include <QSqlError>
#include <string>
#include "image.h"

db::db()
{

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("E:/db/database.db");

    if(!database.open()){
        qDebug() << "Failed to open database\n";
    }
    else{
        qDebug() << "Everything works\n";
    }

}
long long int db::getMaxId(){
    QSqlQuery query;
    query.exec("SELECT MAX(id) FROM images");
    if (query.next()) {
        int largestID = query.value(0).toInt();
        qDebug() << "The largest ID is: " << largestID;
        return largestID;
    } else {
        qDebug() << "Query failed!";
    }

}
void db::saveToDB(QImage& i,QByteArray& h,double s){
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    i.save(&buffer, "PNG");
    buffer.close();

    QSqlQuery query;
    query.prepare("INSERT INTO images (hashsum,similarity,image) VALUES (?, ?, ?)");
    query.addBindValue(h);
    query.addBindValue(s);
    query.addBindValue(imageData);

    if (query.exec()) {
        qDebug() << "Image saved to the database!";
    } else {
        qDebug() << "Failed to save image: " << query.lastError().text();
    }

}
Image db::readFromDB(long long int index){
    QSqlQuery query;
    query.prepare("SELECT image, similarity FROM images WHERE ID = :index");
    query.bindValue(":index", index);
    if (query.exec() && query.first()) {
        QByteArray imageData = query.value(0).toByteArray();
        double s = query.value(1).toDouble();
        QImage image;
        if (image.loadFromData(imageData,"PNG")) {
            Image img = Image(image);
            img.setSimilarty(s);
            return img;

        } else {
            qDebug() << "Failed to load image from data.";
        }
    } else {
        qDebug() << "Failed to retrieve image:1 " << query.lastError().text();
    }

}
db::~db(){
    database.close();

}
