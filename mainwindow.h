
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QScreen>
#include "image.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void takeScreenShot();
    void addImgToLayout(const Image&);

private:
    void readImagesFromDB();
    QGridLayout* layout;
    QPushButton *button;
    QScreen* screen;
    QString filePath;
    QTimer* timer;
    int cur_row;
    int cur_col;
    QImage* prevImage;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
