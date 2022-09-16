#ifndef APPSKELETON_H
#define APPSKELETON_H

#include "sidebar.h"    // for managing sidebar
#include "view3d.h"     // for managing view
#include <QApplication> // for overriding events
#include <QMainWindow>  // inherited from
#include <QWidget>      // parent

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
    QPixmap wireframeViewPix;
    QPixmap wireframeFaceViewPix;
    QPixmap faceViewPix;
    QPixmap faceShadingPix;
    QPixmap quitPix;

    QAction *newTool;
    QAction *openTool;
    QAction *wireframeTool;
    QAction *wireframeFaceTool;
    QAction *faceTool;
    QAction *quitTool;

    View3D *view;
    Sidebar *sidebar;

    void openFileDialog();
    void newScene();
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void wireframeMode();
};

#endif // APPSKELETON_H
