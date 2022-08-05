#include "appskeleton.h"
#include "meshview.h"
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

AppSkeleton::AppSkeleton(QWidget *parent) : QMainWindow(parent)
{
    // Register new images we will use as icons
    QPixmap newFilePix(":pics/pics/clay-icon-new-file.png");
    QPixmap openFilePix(":pics/pics/clay-icon-open-file.png");
    QPixmap quitPix(":pics/pics/clay-icon-exit.png");

    // Adding actions for menu
    QAction *quit = new QAction("&Quit", this);

    // Adding 'File' menu
    QMenu *file;
    file = menuBar()->addMenu("&File");
    file->addAction(quit);

    connect(quit, &QAction::triggered, qApp, &QApplication::quit);

    // Creating a toolbar
    QToolBar *toolbar = addToolBar("Main toolbar");

    // Adding actions for toolbar
    toolbar->addAction(QIcon(newFilePix),"New File");                               // Add a 'New File' action to toolbar
    toolbar->addAction(QIcon(openFilePix),"Open File");                             // Add a 'Open File' action to toolbar
    toolbar->addSeparator();                                                        // Separator --------------------
    QAction *quitTool = toolbar->addAction(QIcon(quitPix), "Quit Application");     // Add a 'Quit' action to toolbar

    connect(quitTool, &QAction::triggered, qApp, &QApplication::quit);

//    //Declare a 3D View
//    MeshView *view = new MeshView(this);
//    // Convert 3D view into a QWidget
//    QWidget *container = QWidget::createWindowContainer(view);
//    // Add widget with the 3D view into the main window
//    layout()->addWidget(view);
}
