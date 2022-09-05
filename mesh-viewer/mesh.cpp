#include "mesh.h"
#include "customeffect.h"
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
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QEffect>

Mesh::Mesh()
{
    meshFilePath = "/home/liz/!Work/mesh-viewer/test-meshes/torus-knot.ply";


    // Setting 3D entities
    rootEntity = new Qt3DCore::QEntity;
    Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(rootEntity);

    // Setting material
    material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(254, 254, 254));

    // Configuring mesh
    meshEntity = new Qt3DRender::QMesh;
    //meshEntity->setSource(QUrl::fromLocalFile(meshFilePath));
    meshEntity->setGeometry(nullptr);
    entity->addComponent(meshEntity);
    entity->addComponent(material);
    //addMaterial(entity);
    //entity->addComponent(material);

    Qt3DCore::QTransform *objectTransform = new Qt3DCore::QTransform(entity);
    entity->addComponent(objectTransform);

    lightEntity = nullptr;
    light = nullptr;

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
void Mesh::setLight(Qt3DRender::QPointLight *newLight)
{
    light = newLight;
}


static const QColor ambientColor("#576675");  // Shader input
static const QColor diffuseColor("#5F6E7D");  // Shader input
static const QColor SpecularColor("#61707F"); // Shader input
static const float shininess(0.5);            // Shader input

void Mesh::addMaterial(Qt3DCore::QEntity *entity)
{
    qDebug() << "!!";
    Qt3DRender::QMaterial * material = new Qt3DRender::QMaterial();
    material->setEffect(new CustomEffect());
    material->addParameter(new Qt3DRender::QParameter(QStringLiteral("ka"), ambientColor));
    material->addParameter(new Qt3DRender::QParameter(QStringLiteral("kd"), diffuseColor));
    material->addParameter(new Qt3DRender::QParameter(QStringLiteral("ks"), SpecularColor));
    material->addParameter(new Qt3DRender::QParameter(QStringLiteral("shininess"), shininess));
    entity->addComponent(material);
}

