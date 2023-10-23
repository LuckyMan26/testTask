
#include "image.h"
#include "qpixmap.h"
#include "QDebug"
#include <QRgb>
#include <QSql>
#include <QBuffer>
#include <QCryptographicHash>
#include <QPainter>
#include <QThread>

db Image::d = db();
Image::Image(QImage& i, QObject* p) : QObject{p}, img(new QImage())
{
    img = new QImage(i);
    hashsum = calculateImageHash();
    similarity = 0;
}
Image::Image(Image& i) : img(new QImage()){

    img = i.img;
    hashsum = i.hashsum;
    similarity = i.similarity;
}
Image::Image(){
    hashsum=0;
    similarity = -1;
    img = new QImage();

}
void Image::setSimilarity(double s){
    similarity = s;
}
//Calculating hashsum of the file
QByteArray Image::calculateImageHash(){
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    img->save(&buffer, "PNG");
    buffer.close();


    QByteArray hash = QCryptographicHash::hash(imageData, QCryptographicHash::Md5);

    return hash.toHex();
}
void Image::setImg(QImage i){
    img = new QImage(i);
}
void Image::setHashSum(QByteArray h){
    hashsum = h;
}
QImage Image::getImg() const{

    return (*img);
}
//Process of saving to db
void Image::saveToDB() {

    d.saveToDB(*img,hashsum,similarity);


}
//Method which calculated similarity to the previous image and save it to db
void Image::handleImage(QImage* prevImage){
    compareToPreviousImage(prevImage);
    saveToDB();
    emit finishedSavingToDB();
}

QPixmap Image::getPixmap(){
    QPixmap m = QPixmap::fromImage(*img);
    return m;
}
//Resizing image to appropriate size(returns new image)
QImage Image::resize(int w,int h) const{

    QImage resizedImage(w, h, QImage::Format_ARGB32);

    QPainter painter(&resizedImage);

    painter.drawImage(0, 0, img->scaled(w, h));

    painter.end();
    return resizedImage;
}
double Image::getSimilarity() const{
    return similarity;
}
//Compares image to another and returns their similarity in the procents
//We calculate number of identical pixel and return similarityPercentage
double Image::compareToPreviousImage(QImage* i){
    if(i==nullptr){
        similarity = -1;
        return -1;
    }
    else{
        if (i->size() != img->size()) {

            return 0.0;
        }

        int width = i->width();
        int height = i->height();
        int totalPixels = width * height;
        int identicalPixels = 0;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                QColor pixelL = i->pixel(x, y);
                QColor pixelR = img->pixel(x, y);


                if (pixelL == pixelR) {
                    identicalPixels++;
                }
            }
        }
        double similarityPercentage = (static_cast<double>(identicalPixels) / totalPixels) * 100.0;
        similarity = similarityPercentage;
        qDebug() << similarity << "\n";
        return similarityPercentage;
    }
}
