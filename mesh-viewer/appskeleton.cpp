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
#include <QTimer>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <Qt3DRender/QCamera>

AppSkeleton::AppSkeleton(QWidget *parent) : QMainWindow(parent)
{
    view = nullptr;
    sidebar = nullptr;

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
    QAction *newTool = toolbar->addAction(QIcon(newFilePix),"New File");            // Add a 'New File' action to toolbar
    QAction *openTool = toolbar->addAction(QIcon(openFilePix), "Open File");        // Add a 'Open File' action to toolbar
    toolbar->addSeparator();                                                        // Separator --------------------
    QAction *quitTool = toolbar->addAction(QIcon(quitPix), "Quit");                 // Add a 'Quit' action to toolbar

    // Add shortcuts
    newTool->setShortcut(tr("CTRL+N"));
    quitTool->setShortcut(tr("CTRL+Q"));
    openTool->setShortcut(tr("CTRL+O"));\

    connect(newTool, &QAction::triggered, this, &AppSkeleton::newScene);
    connect(openTool, &QAction::triggered, this, &AppSkeleton::openFileDialog);
    connect(quitTool, &QAction::triggered, qApp, &QApplication::quit);

    setAcceptDrops(true);
}

void AppSkeleton::setSidebar(Sidebar *newSidebar)
{
    sidebar = newSidebar;
    sidebar->setMesh(view->getMesh());

    // Log action into the sidebar QList
    sidebar->logger->addItem("Loaded file: " + view->getMesh()->getFilePath());
}

void AppSkeleton::setView(View3D *newView)
{
    view = newView;

}

void AppSkeleton::openFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(),("*.ply"));

    view->getMesh()->meshEntity->setSource(QUrl::fromLocalFile(filePath));
    view->getCamera()->viewEntity((Qt3DCore::QEntity *)view->getMesh()->meshEntity);


    // Log action into the sidebar QList
    sidebar->logger->addItem("Loaded file: " + filePath);
//    if (view->getMesh()->meshEntity->status() == Qt3DRender::QMesh::Ready)
//        sidebar->logger->addItem("Loaded file: " + filePath);
//    else if (view->getMesh()->meshEntity->status() == Qt3DRender::QMesh::Error)
//        sidebar->logger->addItem("ERROR: Failed to load mesh");
//    else if (view->getMesh()->meshEntity->status() == Qt3DRender::QMesh::None)
//        sidebar->logger->addItem("Nothing to load");

}

void AppSkeleton::newScene()
{
    view->getMesh()->meshEntity->setGeometry(nullptr);
    sidebar->logger->addItem("Loaded new scene");
}


void AppSkeleton::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void AppSkeleton::dropEvent(QDropEvent *event)
{
    foreach (const QUrl &url, event->mimeData()->urls())
    {
        QString filePath = url.toLocalFile();

        view->getMesh()->meshEntity->setSource(QUrl::fromLocalFile(filePath));
        view->getCamera()->viewEntity((Qt3DCore::QEntity *)view->getMesh()->meshEntity);
//        view->getCamera()->viewAll();
        sidebar->logger->addItem("Dropped file: " + filePath);

        // Log action into the sidebar QList
//        if (view->getMesh()->meshEntity->status() == Qt3DRender::QMesh::Ready)
//            sidebar->logger->addItem("Dropped file: " + filePath);
//        else if (view->getMesh()->meshEntity->status() == Qt3DRender::QMesh::Error)
//            sidebar->logger->addItem("ERROR: Failed to load mesh");
//        else if (view->getMesh()->meshEntity->status() == Qt3DRender::QMesh::None)
//            sidebar->logger->addItem("Nothing to load");



    }
}
