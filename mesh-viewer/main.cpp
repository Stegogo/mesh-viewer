#include "mainwindow.h"
#include "appskeleton.h"

#include <QApplication>
#include <QUrl>                                 // for working with URLs
#include <Qt3DExtras/Qt3DWindow>                // for 3D view
#include <Qt3DExtras/QPhongMaterial>            // for material
#include <Qt3DExtras/QOrbitCameraController>    // for camera control
#include <Qt3DCore/QEntity>                     // for working with 3d entities
#include <Qt3DCore/QTransform>                  // for 3D transform
#include <Qt3DRender/QMesh>                     // for working with meshes
#include <Qt3DRender/QCamera>                   // for camera
#include <Qt3DRender/QPointLight>               // for light

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <Qt3DExtras/qforwardrenderer.h>
#include <QtGui/QScreen>
#include <Qt3DInput/QInputAspect>

#include <Qt3DExtras/QTorusMesh>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppSkeleton mw;
    QUrl data = QUrl::fromLocalFile("/home/liz/!Work/mesh-viewer/test-meshes/sphere.stl");

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

    QWidget *container = QWidget::createWindowContainer(view);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    widget->setWindowTitle(QStringLiteral("Basic shapes"));

    Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
    view->registerAspect(input);

    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;
    Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(rootEntity);


    // Setting material
    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(254, 254, 254));

    // TEMPORARY MESH------------------
    Qt3DExtras::QTorusMesh *m_torus = new Qt3DExtras::QTorusMesh();
    m_torus->setRadius(5.0f);
    m_torus->setMinorRadius(1.5f);
    m_torus->setRings(50);
    m_torus->setSlices(20);
    //---------------------------------

    // Configuring mesh
    Qt3DRender::QMesh *entityMesh = new Qt3DRender::QMesh;
    entityMesh->setMeshName("Mesh");
    entityMesh->setSource(data);
    entity->addComponent(m_torus);
    entity->addComponent(material);

    // Configuring camera
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(40.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 40.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // Setting light
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(0.8f);
    lightEntity->addComponent(light);

    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(0, 0, 40.0f));
    lightEntity->addComponent(lightTransform);

    // Setting camera controller
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setCamera(camera);

    view->setRootEntity(rootEntity);

    mw.setCentralWidget(widget);
    mw.show();
    mw.resize(800, 600);
    return a.exec();
}

