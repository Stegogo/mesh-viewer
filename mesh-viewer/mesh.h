#ifndef MESH_H
#define MESH_H

#include <QUrl>
#include <Qt3DCore/QEntity>
#include <QString>


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

    QString getFilePath();
    void setFilePath(QString filePath);

private:
    QString meshFilePath;

};

#endif // MESH_H
