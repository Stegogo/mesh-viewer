#ifndef APPSKELETON_H
#define APPSKELETON_H

#include "mesh.h"
#include "captionwidget.h"

#include <QApplication>
#include <QUrl>
#include <QMainWindow>
#include <QWidget>

//================================================
// APP SKELETON CLASS
// Provides basic menu & toolbar
//================================================

class AppSkeleton : public QMainWindow
{
    Q_OBJECT
public:
    explicit AppSkeleton(QWidget *parent = nullptr);
    Mesh *mesh;
    CaptionWidget *captionWidget;
private:
    QPixmap newFilePix;
    QPixmap openFilePix;
    QPixmap quitPix;

    void openFileDialog();

    bool event(QEvent *event);
public slots:
    void widgetSizeMove();
};

#endif // APPSKELETON_H
