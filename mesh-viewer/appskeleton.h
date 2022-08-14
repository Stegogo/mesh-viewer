#ifndef APPSKELETON_H
#define APPSKELETON_H

#include "mesh.h"
#include <QApplication>
#include <QUrl>
#include <QMainWindow>
#include <QWheelEvent>
#include <QWidget>

class AppSkeleton : public QMainWindow
{
    Q_OBJECT
public:
    explicit AppSkeleton(QWidget *parent = nullptr);
    Mesh *mesh;
private:
    QPixmap newFilePix;
    QPixmap openFilePix;
    QPixmap quitPix;

    void openFileDialog();
};

#endif // APPSKELETON_H
