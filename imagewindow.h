
#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H


#include <QMainWindow>
#include <QLabel>

class imageWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit imageWindow(const QImage& image,QWidget *parent = nullptr);
private:
      QLabel* imageLabel;
signals:

};

#endif // IMAGEWINDOW_H
