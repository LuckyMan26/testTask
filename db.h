
#ifndef DB_H
#define DB_H


#include <QSql>
#include <QSqlDatabase>
#include <QImage>
class Image;
class db
{
    QSqlDatabase database;
public:
    db();

    void saveToDB(QImage&,QByteArray&,double );
    Image readFromDB(long long int);
    long long int getMaxId();
    long long int getMinId();
    ~db();
};

#endif // DB_H
