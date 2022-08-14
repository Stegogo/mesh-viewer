#include "appskeleton.h"


#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QDebug>
#include <QtCore/QEvent>
#include <QPainter>


AppSkeleton::AppSkeleton(QWidget *parent) : QMainWindow(parent)
{
    mesh = new Mesh();

    // Register new images we will use as icons
    newFilePix = QPixmap(":img/icon-new-file.png");
    openFilePix = QPixmap(":img/icon-open-file.png");
    quitPix = QPixmap(":img/icon-quit.png");

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
    QAction *openTool = toolbar->addAction(QIcon(openFilePix), "Open File");        // Add a 'Open File' action to toolbar
    toolbar->addSeparator();                                                        // Separator --------------------
    QAction *quitTool = toolbar->addAction(QIcon(quitPix), "Quit");                 // Add a 'Quit' action to toolbar

    // Add shortcuts
    quitTool->setShortcut(tr("CTRL+Q"));
    openTool->setShortcut(tr("CTRL+O"));

    connect(openTool, &QAction::triggered, this, &AppSkeleton::openFileDialog);
    connect(quitTool, &QAction::triggered, qApp, &QApplication::quit);
}

void AppSkeleton::openFileDialog()
{
    qDebug() << mesh->getFilePath();
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(),("*.ply"));
    mesh->setFilePath(filePath);

    //====================DANGER ZONE=================
    // It does not actually delete the model and
    // does not help displaying next
    mesh = nullptr;
    //mesh = new Mesh(filePath);
    //qDebug() << mesh->getFilePath();
    //================================================

    this->repaint();
    qApp->processEvents();
}

