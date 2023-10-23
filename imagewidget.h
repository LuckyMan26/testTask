
#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H


#include <QWidget>
#include <QLabel>
#include "image.h"
//Class that consists of Image and label with similarity of the image to the previous one
class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(const Image& i, QWidget *parent = nullptr);
     void setImage(const QImage& image);
private:
    QLabel* label;
    Image* image;
    QLabel *imageLabel;
protected:
    void mousePressEvent (QMouseEvent * event ) override;
private slots:
    //Slot which invokes when we click on this image that allows to open it in a full-screen mode
    void toggleFullscreen();
signals:
    //Signal that emits when we click on the widget
    void clicked();
};

#endif // IMAGEWIDGET_H
