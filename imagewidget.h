
#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H


#include <QWidget>
#include <QLabel>
#include "image.h"

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(Image& i, QWidget *parent = nullptr);
     void setImage(const QImage& image);
private:
    QLabel* label;
    Image* image;
    QLabel *imageLabel;
protected:
    void mousePressEvent (QMouseEvent * event ) override;
private slots:
    void toggleFullscreen();
signals:
    void clicked();
};

#endif // IMAGEWIDGET_H
