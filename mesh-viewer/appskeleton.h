#ifndef APPSKELETON_H
#define APPSKELETON_H

#include "mesh.h"
#include "sidebar.h"

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

    void setSidebar(Sidebar *newSidebar);

private:
    QPixmap newFilePix;
    QPixmap openFilePix;
    QPixmap quitPix;

    Sidebar *sidebar;

    void openFileDialog();
    void newScene();
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // APPSKELETON_H
