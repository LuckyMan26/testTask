
#ifndef DB_H
#define DB_H


#include <QSql>
#include <QSqlDatabase>
#include <QImage>
class db
{
    QSqlDatabase database;
public:
    db();
    static void saveToDB(QImage&,QByteArray&,double );
    void readFromDB(long long int);
    ~db();
};

#endif // DB_H
