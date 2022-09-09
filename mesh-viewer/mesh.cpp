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
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QEffect>
#include <QSlider>

#include <Qt3DRender/QEffect>
#include <Qt3DRender/QMaterial>

#include <Qt3DRender/QGraphicsApiFilter>
#include <QtCore/QUrl>
#include <Qt3DRender/QShaderProgram>
#include <QOpenGLFunctions>

Mesh::Mesh()
{
    meshFilePath = "/home/liz/!Work/mesh-viewer/test-meshes/torus-knot.ply";

    // Setting 3D entities
    rootEntity = new Qt3DCore::QEntity;
    Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(rootEntity);

    // Setting material
    material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(254, 254, 254));

    wireframeMaterial = nullptr;
    wireframeEffect = nullptr;
    wireframeMode = nullptr;
    shininess = nullptr;
    ka = nullptr;
    kd = nullptr;
    ks = nullptr;
    lineColor = nullptr;
    lightIntensity = nullptr;
    addWireframeMaterial();

    // Configuring mesh
    meshEntity = new Qt3DRender::QMesh;
    meshEntity->setSource(QUrl::fromLocalFile(meshFilePath));
    rootEntity->addComponent(meshEntity);
    rootEntity->addComponent(material);

    Qt3DCore::QTransform *objectTransform = new Qt3DCore::QTransform(entity);
    rootEntity->addComponent(objectTransform);

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

void Mesh::addWireframeMaterial()
{

//    not sure abt this
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable( GL_BLEND );
//    glClearColor(0.0,0.0,0.0,0.0);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//    glDepthMask(GL_FALSE);

    // Create custom material
    wireframeMaterial = new Qt3DRender::QMaterial();

    // Create effect, technique, render pass and shader
    wireframeEffect = new Qt3DRender::QEffect();
    Qt3DRender::QTechnique *gl3Technique = new Qt3DRender::QTechnique();
    Qt3DRender::QRenderPass *gl3Pass = new Qt3DRender::QRenderPass();
    Qt3DRender::QShaderProgram *glShader = new Qt3DRender::QShaderProgram();

    // Connect shader code
    glShader->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/wireframe.vert"))));
    glShader->setFragmentShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/wireframe.frag"))));
    glShader->setGeometryShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/wireframe.geom"))));

    // Set the shader on the render pass
    gl3Pass->setShaderProgram(glShader);

    // Create filter
    Qt3DRender::QFilterKey *filterkey = new Qt3DRender::QFilterKey(wireframeMaterial);
    filterkey->setName(QStringLiteral("renderingStyle"));
    filterkey->setValue(QStringLiteral("forward"));

    // Add the pass to the technique
    gl3Technique->addRenderPass(gl3Pass);

    // Set the targeted GL version for the technique
    gl3Technique->graphicsApiFilter()->setProfile(Qt3DRender::QGraphicsApiFilter::CoreProfile);
    gl3Technique->graphicsApiFilter()->setApi(Qt3DRender::QGraphicsApiFilter::OpenGL);
    gl3Technique->graphicsApiFilter()->setMajorVersion(3);
    gl3Technique->graphicsApiFilter()->setMinorVersion(1);

    // Add filter
    gl3Technique->addFilterKey(filterkey);

    // Add the technique to the effect
    wireframeEffect->addTechnique(gl3Technique);

    // Set the effect on the materials
    // and add it to the entity
    wireframeMaterial->setEffect(wireframeEffect);

    // Initialize parameters
    wireframeMode = new Qt3DRender::QParameter(QStringLiteral("mode"), 1);
    ka = new Qt3DRender::QParameter(QStringLiteral("ka"), QVector4D( 0.1, 0.1, 0.1, 0.5 ));
    kd = new Qt3DRender::QParameter(QStringLiteral("kd"), QVector4D( 0.7, 0.7, 0.7, 0.5 ));
    ks = new Qt3DRender::QParameter(QStringLiteral("ks"), QVector4D( 0, 0, 0, 0.5 ));
    shininess = new Qt3DRender::QParameter(QStringLiteral("shininess"), 8);
    lineColor = new Qt3DRender::QParameter(QStringLiteral("line.color"), QVector4D( 1.0, 1.0, 1.0, 1.0 ));
    lightIntensity = new Qt3DRender::QParameter(QStringLiteral("light.intensity"), QVector3D( 0.8, 0.8, 0.8 ));

    // Add parameters for material
    wireframeMaterial->addParameter(ka);
    wireframeMaterial->addParameter(kd);
    wireframeMaterial->addParameter(ks);
    wireframeMaterial->addParameter(shininess);
    wireframeMaterial->addParameter(wireframeMode);

    // Add parameters for effect
    gl3Technique->addParameter(new Qt3DRender::QParameter(QStringLiteral("light.position"), QVector4D( 0.0, 0.0, 0.0, 1.0 )));
    gl3Technique->addParameter(lightIntensity);
    gl3Technique->addParameter(new Qt3DRender::QParameter(QStringLiteral("line.width"), 1.0));
    gl3Technique->addParameter(lineColor);

}

