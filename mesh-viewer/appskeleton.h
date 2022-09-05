#ifndef APPSKELETON_H
#define APPSKELETON_H

#include "sidebar.h"
#include "view3d.h"
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
    void setSidebar(Sidebar *newSidebar);

    void setView(View3D *newView);

private:
    QPixmap newFilePix;
    QPixmap openFilePix;
    QPixmap quitPix;

    View3D *view;
    Sidebar *sidebar;

    void openFileDialog();
    void newScene();
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // APPSKELETON_H
