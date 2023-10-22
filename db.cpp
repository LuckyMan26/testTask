
#include "db.h"
#include <QDebug>
#include <QFile>
#include <QBuffer>
#include <QSqlQuery>
#include <QSqlError>
#include <string>

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
void db::readFromDB(long long int index){
    QSqlQuery query;
    query.prepare("SELECT image FROM images WHERE ID = :index");
    query.bindValue(":index", index);
    if (query.exec() && query.first()) {
        QByteArray imageData = query.value(0).toByteArray();
        QImage image;
        if (image.loadFromData(imageData,"PNG")) {

            image.save("E:/dbimg/image.png");
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
