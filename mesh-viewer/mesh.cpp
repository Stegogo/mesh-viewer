#include "mesh.h"

#include <QUrl>                                 // for working with URLs
#include <Qt3DExtras/Qt3DWindow>                // for 3D view
#include <Qt3DExtras/QPhongMaterial>            // for material
#include <Qt3DExtras/QOrbitCameraController>    // for camera control
#include <Qt3DCore/QEntity>                     // for working with 3d entities
#include <Qt3DCore/QTransform>                  // for 3D transform
#include <Qt3DRender/QMesh>                     // for working with meshes
#include <Qt3DRender/QCamera>                   // for camera
#include <Qt3DRender/QPointLight>               // for light

Mesh::Mesh()
{
    meshFilePath = QUrl::fromLocalFile("/home/liz/!Work/mesh-viewer/test-meshes/torus-knot.ply");

    // Setting 3D entities
    rootEntity = new Qt3DCore::QEntity;
    Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(rootEntity);

    // Setting material
    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(254, 254, 254));

    // Configuring mesh
    Qt3DRender::QMesh *entityMesh = new Qt3DRender::QMesh;
    entityMesh->setMeshName("Mesh");
    entityMesh->setSource(meshFilePath);
    entity->addComponent(entityMesh);
    entity->addComponent(material);

    // Setting light
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(0.8f);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(0, 0, 40.0f));
    lightEntity->addComponent(lightTransform);
}

QUrl Mesh::getFilePath()
{
    return meshFilePath;
}

void Mesh::setFilePath(QUrl filePath)
{
    meshFilePath = filePath;
}
