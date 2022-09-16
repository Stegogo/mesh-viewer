#ifndef MESH_H
#define MESH_H

#include <Qt3DCore/QEntity>     // for managing entities
#include <Qt3DRender/QMesh>     // for mesh entitiy
#include <Qt3DRender/QPointLight>   // light
#include <Qt3DCore/QTransform>      // transform
#include <QMaterial>                // for custom materials
#include <Qt3DRender/QTechnique>    // for shader effects

//================================================
// MESH CLASS
// Describes a mesh.
//================================================

class Mesh
{
public:
    Mesh();
    Qt3DCore::QEntity *rootEntity;
    Qt3DRender::QMesh *meshEntity;
    Qt3DCore::QEntity *lightEntity;
    Qt3DRender::QPointLight *light;
    Qt3DCore::QTransform *transform;

    Qt3DRender::QMaterial *wireframeMaterial;
    Qt3DRender::QEffect *wireframeEffect;
    Qt3DRender::QShaderProgram *glShader;

    Qt3DRender::QParameter *wireframeMode;
    Qt3DRender::QParameter *shininess;
    Qt3DRender::QParameter *ka;
    Qt3DRender::QParameter *kd;
    Qt3DRender::QParameter *ks;
    Qt3DRender::QParameter *lineColor;
    Qt3DRender::QParameter *lineWidth;
    Qt3DRender::QParameter *lightIntensity;
    Qt3DRender::QParameter *lightPosition;
    Qt3DRender::QParameter *lightColor;

    void setLight(Qt3DRender::QPointLight *newLight);
    void addWireframeMaterial();

private:
    QString meshFilePath;
};

#endif // MESH_H
