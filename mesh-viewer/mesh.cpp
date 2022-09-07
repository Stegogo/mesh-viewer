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
#include <QSlider>

#include <Qt3DRender/QEffect>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QGraphicsApiFilter>
#include <QtCore/QUrl>
#include <Qt3DRender/QShaderProgram>
#include <QMaterial>

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
    meshEntity->setSource(QUrl::fromLocalFile(meshFilePath));
    //meshEntity->setGeometry(nullptr);
    rootEntity->addComponent(meshEntity);
    //entity->addComponent(meshEntity);
    rootEntity->addComponent(material);
    //entity->addComponent(material);
    //addMaterial(rootEntity);
    //entity->addComponent(material);

    //!-----------------------DANGER ZONE---------------------------
    //!-----------------------DANGER ZONE---------------------------

//    Qt3DRender::QMaterial *material1 = new Qt3DRender::QMaterial();
//    Qt3DRender::QMaterial *material2 = new Qt3DRender::QMaterial();

//    // Create effect, technique, render pass and shader
//    Qt3DRender::QEffect *effect = new Qt3DRender::QEffect();
//    Qt3DRender::QTechnique *gl3Technique = new Qt3DRender::QTechnique();
//    Qt3DRender::QRenderPass *gl3Pass = new Qt3DRender::QRenderPass();
//    Qt3DRender::QShaderProgram *glShader = new Qt3DRender::QShaderProgram();

//    // Set the shader on the render pass
//    glShader->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/custom-shader.vert"))));
//    glShader->setFragmentShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/custom-shader.frag"))));
//    gl3Pass->setShaderProgram(glShader);

//    // Add the pass to the technique
//    gl3Technique->addRenderPass(gl3Pass);

//    // Set the targeted GL version for the technique
//    gl3Technique->graphicsApiFilter()->setApi(Qt3DRender::QGraphicsApiFilter::OpenGL);
//    gl3Technique->graphicsApiFilter()->setMajorVersion(3);
//    gl3Technique->graphicsApiFilter()->setMinorVersion(1);
//    gl3Technique->graphicsApiFilter()->setProfile(Qt3DRender::QGraphicsApiFilter::CoreProfile);

//    // Add the technique to the effect
//    effect->addTechnique(gl3Technique);

//    // Set the effect on the materials
//    material1->setEffect(effect);
//    material2->setEffect(effect);

//    // Set different parameters on the materials
//    const QString parameterName = QStringLiteral("color");
//    material1->addParameter(new Qt3DRender::QParameter(parameterName, QColor::fromRgbF(0.0f, 1.0f, 0.0f, 1.0f)));
//    material2->addParameter(new Qt3DRender::QParameter(parameterName, QColor::fromRgbF(1.0f, 1.0f, 1.0f, 1.0f)));

//    rootEntity->addComponent(material1);
//    //rootEntity->addComponent(material2);
//    entity->addComponent(material1);
//    //entity->addComponent(material2);

    //!-----------------------DANGER ZONE---------------------------
    //!-----------------------DANGER ZONE---------------------------

    Qt3DCore::QTransform *objectTransform = new Qt3DCore::QTransform(entity);
    rootEntity->addComponent(objectTransform);

    qDebug() << rootEntity->components();


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



void Mesh::addMaterial(Qt3DCore::QEntity *entity)
{
    qDebug() << "material!!";

    QColor ambientColor(25, 25, 25);  // Shader input
    QColor diffuseColor(25, 25, 25);  // Shader input
    QColor SpecularColor(25, 25, 25); // Shader input
    float shininess(0.0);            // Shader input

//    Qt3DRender::QMaterial * material = new Qt3DRender::QMaterial();
    Qt3DRender::QMaterial * material = new Qt3DRender::QMaterial();
//    material->setEffect(new CustomEffect());
    material->addParameter(new Qt3DRender::QParameter(QStringLiteral("ka"), ambientColor));
    material->addParameter(new Qt3DRender::QParameter(QStringLiteral("kd"), diffuseColor));
    material->addParameter(new Qt3DRender::QParameter(QStringLiteral("ks"), SpecularColor));
    material->addParameter(new Qt3DRender::QParameter(QStringLiteral("shininess"), shininess));


    //material->setDiffuse(QColor(25, 25, 25));
    entity->addComponent(material);
}
