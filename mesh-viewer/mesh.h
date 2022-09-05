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

    QString getFilePath();
    void setFilePath(QString filePath);
    void setLight(Qt3DRender::QPointLight *newLight);

private:
    QString meshFilePath;

    void addMaterial(Qt3DCore::QEntity *entity);
};

#endif // MESH_H
