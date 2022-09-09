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
#include <Qt3DRender/QParameter>

AppSkeleton::AppSkeleton(QWidget *parent) : QMainWindow(parent)
{
    view = nullptr;
    sidebar = nullptr;

    // Register new images we will use as icons
    newFilePix = QPixmap(":img/icon-new-file.png");
    openFilePix = QPixmap(":img/icon-open-file.png");
    wireframeViewPix = QPixmap(":img/icon-wireframe.png");
    wireframeFaceViewPix = QPixmap(":img/icon-wireframe-face.png");
    faceViewPix = QPixmap(":img/icon-face.png");
    quitPix = QPixmap(":img/icon-quit.png");

    // Creating a toolbar
    QToolBar *toolbar = addToolBar("Main toolbar");

    // Adding actions for toolbar
    newTool = toolbar->addAction(QIcon(newFilePix),"New File");            // Add a 'New File' action to toolbar
    openTool = toolbar->addAction(QIcon(openFilePix), "Open File");        // Add a 'Open File' action to toolbar

    toolbar->addSeparator();                                                        // Separator --------------------

    wireframeTool = toolbar->addAction(QIcon(wireframeViewPix),"Wireframe only");
    wireframeFaceTool = toolbar->addAction(QIcon(wireframeFaceViewPix),"Wireframe + Face");
    faceTool = toolbar->addAction(QIcon(faceViewPix),"Face only");

    toolbar->addSeparator();                                                        // Separator --------------------

    quitTool = toolbar->addAction(QIcon(quitPix), "Quit");                 // Add a 'Quit' action to toolbar

    // Add shortcuts
    newTool->setShortcut(tr("CTRL+N"));
    quitTool->setShortcut(tr("CTRL+Q"));
    openTool->setShortcut(tr("CTRL+O"));

    connect(newTool, &QAction::triggered, this, &AppSkeleton::newScene);
    connect(openTool, &QAction::triggered, this, &AppSkeleton::openFileDialog);
    connect(wireframeTool, &QAction::triggered, this, &AppSkeleton::wireframeMode);
    connect(wireframeFaceTool, &QAction::triggered, this, &AppSkeleton::wireframeMode);
    connect(faceTool, &QAction::triggered, this, &AppSkeleton::wireframeMode);
    connect(quitTool, &QAction::triggered, qApp, &QApplication::quit);

    setAcceptDrops(true);

}

void AppSkeleton::setSidebar(Sidebar *newSidebar)
{
    sidebar = newSidebar;
    sidebar->setMesh(view->getMesh());

    // Log action into the sidebar QList
    sidebar->logger->addItem("Loaded new scene");
}

void AppSkeleton::setView(View3D *newView)
{
    view = newView;

}

void AppSkeleton::openFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("All known formats(*.ply *.obj *.stl);;.ply(*.ply);;.obj(*.obj);; Binary STL(*.stl)"));

    if ((filePath.endsWith(".ply",Qt::CaseSensitive)) || (filePath.endsWith(".obj",Qt::CaseSensitive)) || (filePath.endsWith(".stl",Qt::CaseSensitive)))
    {
        view->getMesh()->meshEntity->setSource(QUrl::fromLocalFile(filePath));
        view->getCamera()->viewEntity((Qt3DCore::QEntity *)view->getMesh()->meshEntity);
        // Log action into the sidebar QList
        sidebar->logger->addItem("Loaded file: " + filePath);
    }
    else
    {
       sidebar->logger->addItem("ERROR: Failed opening file");
    }

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

        if ((filePath.endsWith(".ply",Qt::CaseSensitive)) || (filePath.endsWith(".obj",Qt::CaseSensitive)) || (filePath.endsWith(".stl",Qt::CaseSensitive)))
        {
            view->getMesh()->meshEntity->setSource(QUrl::fromLocalFile(filePath));
            view->getCamera()->viewEntity((Qt3DCore::QEntity *)view->getMesh()->meshEntity);

            // Log action into the sidebar QList
            sidebar->logger->addItem("Dropped file: " + filePath);
        }
        else
           sidebar->logger->addItem("ERROR: Failed opening file");
    }
}

void AppSkeleton::wireframeMode()
{
    // Wireframe ONLY
    if (QObject::sender() == wireframeTool)
        view->getMesh()->wireframeMode->setValue(1);
    // Wireframe + Face
    else if (QObject::sender() == wireframeFaceTool)
        view->getMesh()->wireframeMode->setValue(2);
    // Face ONLY
    else if (QObject::sender() == faceTool)
        view->getMesh()->wireframeMode->setValue(0);
}
