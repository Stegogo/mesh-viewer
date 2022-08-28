#include "mesh.h"

#include <QUrl>                                 // for working with URLs
#include <Qt3DExtras/Qt3DWindow>                // for 3D view
#include <Qt3DExtras/QPhongMaterial>            // for material
#include <Qt3DExtras/QOrbitCameraController>    // for camera control
#include <Qt3DCore/QEntity>                     // for working with 3d entities
#include <Qt3DCore/QTransform>                  // for 3D transform
#include <Qt3DRender/QMesh>                     // for working with meshes
#include <Qt3DRender/QCamera>                   // for camera
#include <QDebug>
#include <Qt3DRender/QSceneLoader>
#include <Qt3DRender/QAttribute>
#include <QApplication>



Mesh::Mesh()
{
    meshFilePath = "/home/liz/!Work/mesh-viewer/test-meshes/torus-knot.ply";


    // Setting 3D entities
    rootEntity = new Qt3DCore::QEntity;
    Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(rootEntity);

    //Qt3DRender::QSceneLoader *sceneLoader = new Qt3DRender::QSceneLoader(entity);
    //sceneLoader->setSource(QUrl::fromLocalFile(meshFilePath));

    // Setting material
    material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(254, 254, 254));

    // Configuring mesh
    meshEntity = new Qt3DRender::QMesh;
    meshEntity->setSource(QUrl::fromLocalFile(meshFilePath));
    entity->addComponent(meshEntity);
    entity->addComponent(material);

    Qt3DCore::QTransform *objectTransform = new Qt3DCore::QTransform(entity);
    entity->addComponent(objectTransform);

    // Setting light
    lightEntity = new Qt3DCore::QEntity(rootEntity);
    light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(0.8f);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(0, 0, 40.0f));
    lightEntity->addComponent(lightTransform);

    //entity->removeComponent(entityMesh);

    qApp->processEvents();
}

Mesh::Mesh(const QString &filePath)
{
    meshFilePath = filePath;

    // Setting 3D entities
    rootEntity = new Qt3DCore::QEntity;
    Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(rootEntity);

    // Setting material
    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(254, 254, 254));

    // Configuring mesh
    Qt3DRender::QMesh *entityMesh = new Qt3DRender::QMesh;
    //entityMesh->setMeshName("Mesh");
    entityMesh->setSource(QUrl::fromLocalFile(meshFilePath));
    entity->addComponent(entityMesh);
    entity->addComponent(material);

    qDebug() << entityMesh->source();

    Qt3DCore::QTransform *objectTransform = new Qt3DCore::QTransform(entity);
    entity->addComponent(objectTransform);

    // Setting light
    lightEntity = new Qt3DCore::QEntity(rootEntity);
    light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(0.8f);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(0, 0, 40.0f));
    lightEntity->addComponent(lightTransform);

    qApp->processEvents();
}


QString Mesh::getFilePath()
{
    return meshFilePath;
}

void Mesh::setFilePath(QString filePath)
{
    meshFilePath = filePath;

}

//void Mesh::setDiffuse(QColor color)
//{
////    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
////    material->setDiffuse(Qt::red);
////    qDebug() << material->diffuse();
////    rootEntity->removeComponent(material);
////    rootEntity->addComponent(material);
//    //light->setColor("blue");


//}
