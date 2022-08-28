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
    Mesh(const QString &filePath);
    Qt3DCore::QEntity *rootEntity;
    Qt3DRender::QMesh *meshEntity;
    Qt3DCore::QEntity *lightEntity;
    Qt3DRender::QPointLight *light;
    Qt3DExtras::QPhongMaterial *material;

    QString getFilePath();
    void setFilePath(QString filePath);
private:
    QString meshFilePath;

};

#endif // MESH_H
