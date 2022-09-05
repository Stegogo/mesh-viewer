#include "appskeleton.h"
#include "camcontroller.h"
#include "view3d.h"
#include "sidebar.h"


#include <QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QUrl>                                 // for working with URLs
#include <Qt3DExtras/Qt3DWindow>                // for 3D view
#include <Qt3DExtras/QPhongMaterial>            // for material
#include <Qt3DExtras/QOrbitCameraController>    // for camera control
#include <Qt3DCore/QEntity>                     // for working with 3d entities
#include <Qt3DCore/QTransform>                  // for 3D transform
#include <Qt3DRender/QMesh>                     // for working with meshes
#include <Qt3DRender/QCamera>                   // for camera
#include <Qt3DRender/QDirectionalLight>         // for light
#include <Qt3DExtras/qforwardrenderer.h>        // for FrameGraph
#include <Qt3DInput/QInputAspect>               // for 3D input                 
#include <QSplitter>                            // for sidebar splitter
#include <QSizeGrip>                            // for resizing the sidebar

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppSkeleton mw;

    // Setting up windows and widgets
    View3D *view = new View3D();
    mw.setView(view);
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    QWidget *container = QWidget::createWindowContainer(view);
    QWidget *widget = new QWidget;

    // Setting up sidebar
    Sidebar *sidebar = new Sidebar(widget);
    mw.setSidebar(sidebar);
    sidebar->setMesh(view->getMesh());

    // Configuring layouts
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    view->setWidget(container);
    vLayout->addWidget(sidebar);

    // Configuring camera
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(40.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 400.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

     // Setting camera controller
    CamController * camController = new CamController(view->getMesh()->rootEntity);
    camController->setCamera(camera);


    // Setting a spliiter for adjusting the sidebar size
    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(widget);
    splitter->addWidget(sidebar);


    // Set the initial sizes for QSplitter widgets
    splitter->setSizes(QList<int>{500, 200});

    view->setCamera(camera);
    view->setRootEntity(view->getMesh()->rootEntity);

    camera->viewEntity(view->getMesh()->rootEntity);
    camera->viewAll();

    mw.setWindowTitle(QStringLiteral("MeshView"));
    mw.setCentralWidget(splitter);
    mw.show();
    mw.resize(800, 600);


    return a.exec();
}

