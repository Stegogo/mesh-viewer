#include "appskeleton.h"

#include <QToolBar>                 // for toolbar
#include <QIcon>                    // for toolbar icons
#include <QAction>                  // for toolbar actions
#include <QFileDialog>              // file open dialog
#include <QDragEnterEvent>          // for drag & drop
#include <QDropEvent>               // for drag & drop
#include <QMimeData>                // for drag & drop
#include <Qt3DRender/QCamera>       // managing camera
#include <Qt3DRender/QParameter>    // managing material parameters

//-----------------------------------------
// Constructor
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
    newTool = toolbar->addAction(QIcon(newFilePix),"New File");
    openTool = toolbar->addAction(QIcon(openFilePix), "Open File");
    toolbar->addSeparator();
    wireframeTool = toolbar->addAction(QIcon(wireframeViewPix),"Wireframe only");
    wireframeFaceTool = toolbar->addAction(QIcon(wireframeFaceViewPix),"Wireframe + Face");
    faceTool = toolbar->addAction(QIcon(faceViewPix),"Face only");
    toolbar->addSeparator();
    quitTool = toolbar->addAction(QIcon(quitPix), "Quit");

    // Add shortcuts
    newTool->setShortcut(tr("CTRL+N"));
    quitTool->setShortcut(tr("CTRL+Q"));
    openTool->setShortcut(tr("CTRL+O"));

    // Set checked status for buttons
    wireframeTool->setCheckable(true);
    wireframeFaceTool->setCheckable(true);
    faceTool->setCheckable(true);
    faceTool->setChecked(true);

    // Connect to methods
    connect(newTool, &QAction::triggered, this, &AppSkeleton::newScene);
    connect(openTool, &QAction::triggered, this, &AppSkeleton::openFileDialog);
    connect(wireframeTool, &QAction::triggered, this, &AppSkeleton::wireframeMode);
    connect(wireframeFaceTool, &QAction::triggered, this, &AppSkeleton::wireframeMode);
    connect(faceTool, &QAction::triggered, this, &AppSkeleton::wireframeMode);
    connect(quitTool, &QAction::triggered, qApp, &QApplication::quit);

    // accept drag & drop
    setAcceptDrops(true);

}

//-----------------------------------------
// Setter for sidebar (also sets mesh for sidebar
// and adds a corresponding logger entry)
void AppSkeleton::setSidebar(Sidebar *newSidebar)
{
    sidebar = newSidebar;
    sidebar->setMesh(view->getMesh());

    // Log action into the sidebar QList
    sidebar->logger->addItem("Loaded new scene");
}

//-----------------------------------------
// Setter for view
void AppSkeleton::setView(View3D *newView)
{
    view = newView;
}

//-----------------------------------------
// Display an 'open file' dialog, and
// reload mesh on success,
// and inform about error otherwise
void AppSkeleton::openFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("All known formats(*.ply *.obj *.stl);;.ply(*.ply);;.obj(*.obj);; Binary STL(*.stl)"));

    // A restriction to open only .PLY, .OBJ or .STL files to avoid and catch errors
    if ((filePath.endsWith(".ply",Qt::CaseSensitive)) || (filePath.endsWith(".obj",Qt::CaseSensitive)) || (filePath.endsWith(".stl",Qt::CaseSensitive)))
    {
        // Reload mesh
        view->getMesh()->meshEntity->setSource(QUrl::fromLocalFile(filePath));
        view->getCamera()->viewEntity((Qt3DCore::QEntity *)view->getMesh()->meshEntity);

        // Log action into the sidebar QList
        sidebar->logger->addItem("Loaded file: " + filePath);
    }
    else
       sidebar->logger->addItem("ERROR: Failed opening file");

}

//-----------------------------------------
// Reset the scene, clear geometry
void AppSkeleton::newScene()
{
    view->getMesh()->meshEntity->setGeometry(nullptr);
    view->getCamera()->setPosition(QVector3D(0, 0, 400.0f));
    view->getCamera()->setViewCenter(QVector3D(0, 0, 0));
    view->getCamera()->setFieldOfView(1);
    sidebar->logger->addItem("Loaded new scene");

}

//-----------------------------------------
// Drag enter event
void AppSkeleton::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

//-----------------------------------------
// Drop event
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

//-----------------------------------------
// Wireframe mode selector for actions on the toolbaar
void AppSkeleton::wireframeMode()
{
    // Wireframe ONLY
    if (QObject::sender() == wireframeTool)
    {
        view->getMesh()->wireframeMode->setValue(1);

        wireframeTool->setChecked(true);
        wireframeFaceTool->setChecked(false);
        faceTool->setChecked(false);
    }
    // Wireframe + Face
    else if (QObject::sender() == wireframeFaceTool)
    {
        view->getMesh()->wireframeMode->setValue(2);

        wireframeTool->setChecked(false);
        wireframeFaceTool->setChecked(true);
        faceTool->setChecked(false);
    }
    // Face ONLY
    else if (QObject::sender() == faceTool)
    {
        view->getMesh()->wireframeMode->setValue(0);

        wireframeTool->setChecked(false);
        wireframeFaceTool->setChecked(false);
        faceTool->setChecked(true);
    }
}
