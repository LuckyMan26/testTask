QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    db.cpp \
    handleimagetask.cpp \
    image.cpp \
    imagewidget.cpp \
    imagewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    readingfromdb.cpp

HEADERS += \
    db.h \
    handleimagetask.h \
    image.h \
    imagewidget.h \
    imagewindow.h \
    mainwindow.h \
    readingfromdb.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
