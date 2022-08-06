#ifndef MESH_H
#define MESH_H

#include <QUrl>
#include <Qt3DCore/QEntity>

class Mesh
{
public:
    Mesh();
    Qt3DCore::QEntity *rootEntity;

    QUrl getFilePath();
    void setFilePath(QUrl filePath);
private:
    QUrl meshFilePath;
};

#endif // MESH_H
