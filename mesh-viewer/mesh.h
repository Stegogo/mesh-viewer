#ifndef MESH_H
#define MESH_H

#include <QUrl>
#include <Qt3DCore/QEntity>
#include <QString>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QPointLight>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QTechnique>
#include <Qt3DCore/QTransform>

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

    QString getFilePath();
    void setFilePath(QString filePath);
    void setLight(Qt3DRender::QPointLight *newLight);
    void addWireframeMaterial();
    //void addFaceShadingMaterial();

private:
    QString meshFilePath;
};

#endif // MESH_H
