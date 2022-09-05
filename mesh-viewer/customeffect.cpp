#include "customeffect.h"

#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QGraphicsApiFilter>
#include <QtCore/QUrl>
#include <Qt3DRender/QShaderProgram>

CustomEffect::CustomEffect(Qt3DCore::QNode *parent)
    : Qt3DRender::QEffect(parent)
{

    Qt3DRender::QTechnique *techniqueES20 = new Qt3DRender::QTechnique();
    techniqueES20->graphicsApiFilter()->setProfile(Qt3DRender::QGraphicsApiFilter::NoProfile);
    techniqueES20->graphicsApiFilter()->setApi(Qt3DRender::QGraphicsApiFilter::OpenGLES);
    techniqueES20->graphicsApiFilter()->setMajorVersion(2);
    techniqueES20->graphicsApiFilter()->setMinorVersion(0);

    Qt3DRender::QTechnique *techniqueGL31 = new Qt3DRender::QTechnique();
    techniqueGL31->graphicsApiFilter()->setProfile(Qt3DRender::QGraphicsApiFilter::CoreProfile);
    techniqueGL31->graphicsApiFilter()->setApi(Qt3DRender::QGraphicsApiFilter::OpenGL);
    techniqueGL31->graphicsApiFilter()->setMajorVersion(3);
    techniqueGL31->graphicsApiFilter()->setMinorVersion(1);

    Qt3DRender::QFilterKey *filterkey = new Qt3DRender::QFilterKey(this);
    filterkey->setName(QStringLiteral("renderingStyle"));
    filterkey->setValue(QStringLiteral("forward"));

    techniqueES20->addFilterKey(filterkey);
    techniqueGL31->addFilterKey(filterkey);

    Qt3DRender::QShaderProgram *shader2 = new Qt3DRender::QShaderProgram();
    shader2->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/custom-shader.vert"))));
    shader2->setFragmentShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/custom-shader.frag"))));

    Qt3DRender::QShaderProgram *shader3 = new Qt3DRender::QShaderProgram();
    shader3->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/custom-shader.vert"))));
    shader3->setFragmentShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/custom-shader.frag"))));

    Qt3DRender::QRenderPass *renderPass2 = new Qt3DRender::QRenderPass();
    renderPass2->setShaderProgram(shader2);

    Qt3DRender::QRenderPass *renderPass3 = new Qt3DRender::QRenderPass();
    renderPass3->setShaderProgram(shader3);

    techniqueES20->addRenderPass(renderPass2);
    techniqueGL31->addRenderPass(renderPass3);

    addTechnique(techniqueES20);
    addTechnique(techniqueGL31);
}
