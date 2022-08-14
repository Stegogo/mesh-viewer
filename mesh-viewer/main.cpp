#include "appskeleton.h"
#include "camcontroller.h"
#include "view3d.h"

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
#include <Qt3DRender/QPointLight>               // for light
#include <Qt3DExtras/qforwardrenderer.h>        // for FrameGraph
#include <Qt3DInput/QInputAspect>               // for 3D input

#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppSkeleton mw;

    // Setting up windows and widgets
    View3D *view = new View3D();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

    QWidget *container = QWidget::createWindowContainer(view);

    QWidget *widget = new QWidget;

    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    view->setWidget(container);

    QPushButton *add = new QPushButton("button");
    vLayout->addWidget(add);

    // Configuring camera
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(40.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 20.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // Setting camera controller
    CamController * camController = new CamController(mw.mesh->rootEntity);
    camController->setCamera(camera);
    view->setCamera(camera);

    view->setRootEntity(mw.mesh->rootEntity);
    mw.setWindowTitle(QStringLiteral("MeshView"));
    mw.setCentralWidget(widget);
    mw.show();
    mw.resize(800, 600);



    return a.exec();
}

