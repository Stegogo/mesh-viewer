#include "mesh.h"

#include <QApplication>                 // for qApp
#include <Qt3DRender/QParameter>        // for custom material
#include <Qt3DRender/QEffect>           // for custom material
#include <Qt3DRender/QGraphicsApiFilter>// for custom material
#include <Qt3DRender/QEffect>           // for custom material
#include <Qt3DRender/QShaderProgram>    // for custom material
#include <QOpenGLFunctions>             // for OpenGL

//-----------------------------------------
// Constructor
Mesh::Mesh()
{
    // Setting 3D entities
    rootEntity = new Qt3DCore::QEntity;
    Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(rootEntity);

    wireframeMode = nullptr;
    shininess = nullptr;
    ka = nullptr;
    kd = nullptr;
    ks = nullptr;
    lineColor = nullptr;
    lightIntensity = nullptr;
    lightPosition = nullptr;
    lightColor = nullptr;
    lineWidth = nullptr;

    // Register default material
    wireframeMaterial = nullptr;
    wireframeEffect = nullptr;
    glShader = nullptr;
    addWireframeMaterial();

    // Configuring mesh
    meshEntity = new Qt3DRender::QMesh;
    rootEntity->addComponent(meshEntity);
    meshEntity->setGeometry(nullptr);
    rootEntity->addComponent(wireframeMaterial);

    transform = new Qt3DCore::QTransform(entity);

    rootEntity->addComponent(transform);

    lightEntity = nullptr;
    light = nullptr;

    qApp->processEvents();
}

//-----------------------------------------
// Setter for light
void Mesh::setLight(Qt3DRender::QPointLight *newLight)
{
    light = newLight;
}

//-----------------------------------------
// Add custom material to mesh
void Mesh::addWireframeMaterial()
{
    //OpenGL functions
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthMask(GL_FALSE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glFrontFace(GL_CCW);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    // Create custom material
    wireframeMaterial = new Qt3DRender::QMaterial();

    // Create effect, technique, render pass and shader
    wireframeEffect = new Qt3DRender::QEffect();
    Qt3DRender::QTechnique *gl3Technique = new Qt3DRender::QTechnique();
    Qt3DRender::QRenderPass *gl3Pass = new Qt3DRender::QRenderPass();
    glShader = new Qt3DRender::QShaderProgram();

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
    wireframeMode = new Qt3DRender::QParameter(QStringLiteral("mode"), 0);
    ka = new Qt3DRender::QParameter(QStringLiteral("ka"), QVector4D( 0.1, 0.1, 0.1, 1.0 ));
    kd = new Qt3DRender::QParameter(QStringLiteral("kd"), QVector4D( 1, 1, 1, 1.0 ));
    ks = new Qt3DRender::QParameter(QStringLiteral("ks"), QVector4D( 5, 5, 5, 1.0 ));
    shininess = new Qt3DRender::QParameter(QStringLiteral("shininess"), 500);
    lineColor = new Qt3DRender::QParameter(QStringLiteral("line.color"), QVector4D( 1.0, 1.0, 1.0, 1.0 ));
    lineWidth = new Qt3DRender::QParameter(QStringLiteral("line.width"), 1.0);
    lightIntensity = new Qt3DRender::QParameter(QStringLiteral("light.intensity"), QVector3D( 0.8, 0.8, 0.8 ));
    lightPosition = new Qt3DRender::QParameter(QStringLiteral("light.position"), QVector4D( 0.0, 0.0, 0.0, 1.0 ));
    lightColor = new Qt3DRender::QParameter(QStringLiteral("light.color"), QVector4D( 1, 1, 1, 1));

    // Add parameters for material
    wireframeMaterial->addParameter(ka);
    wireframeMaterial->addParameter(kd);
    wireframeMaterial->addParameter(ks);
    wireframeMaterial->addParameter(shininess);
    wireframeMaterial->addParameter(wireframeMode);

    // Add parameters for effect
    gl3Technique->addParameter(lightPosition);
    gl3Technique->addParameter(lineWidth);
    gl3Technique->addParameter(lineColor);
    gl3Technique->addParameter(lightIntensity);
    gl3Technique->addParameter(lightColor);
    wireframeMaterial->addParameter(new Qt3DRender::QParameter(QStringLiteral("shade"), 1));
}

