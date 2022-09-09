#ifndef MESH_H
#define MESH_H

#include <QUrl>
#include <Qt3DCore/QEntity>
#include <QString>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QPointLight>
#include <Qt3DExtras/QPhongMaterial>

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

    Qt3DExtras::QPhongMaterial *material;
    Qt3DRender::QMaterial *wireframeMaterial;
    Qt3DRender::QEffect *wireframeEffect;

    Qt3DRender::QParameter *wireframeMode;
    Qt3DRender::QParameter *shininess;
    Qt3DRender::QParameter *ka;
    Qt3DRender::QParameter *kd;
    Qt3DRender::QParameter *ks;

    QString getFilePath();
    void setFilePath(QString filePath);
    void setLight(Qt3DRender::QPointLight *newLight);
    void addWireframeMaterial();

private:
    QString meshFilePath;
};

#endif // MESH_H
