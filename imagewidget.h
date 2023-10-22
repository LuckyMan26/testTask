
#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H


#include <QWidget>
#include <QLabel>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);
     void setImage(const QImage& image);
private:
    QLabel* label;
    QImage image;
    QLabel *imageLabel;
protected:
    void mousePressEvent (QMouseEvent * event ) override;
private slots:
    void toggleFullscreen();
signals:
    void clicked();
};

#endif // IMAGEWIDGET_H
