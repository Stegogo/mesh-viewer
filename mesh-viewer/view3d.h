#ifndef VIEW3D_H
#define VIEW3D_H

#include "mesh.h"
#include <QWidget>                  // for overrides
#include <Qt3DExtras/Qt3DWindow>    // inherited from
#include <QWheelEvent>              // for zoom
#include <Qt3DCore/QTransform>      // mesh transform
#include <Qt3DRender/QPointLight>   // light
#include <Qt3DRender/QCamera>       // camera

//================================================
// VIEW 3D CLASS
// Manages events for 3D window, e.g. wheelEvent.
//================================================

class View3D : public Qt3DExtras::Qt3DWindow
{
    Q_OBJECT
public:
    View3D();
    void setWidget(QWidget *newContainer);

    void setCamera(Qt3DRender::QCamera *newCamera);
    Qt3DRender::QCamera *getCamera();

    Mesh *getMesh() const;
    void setMesh(Mesh *newMesh);

    Qt3DCore::QEntity *getLightEntity() const;
    void setLightEntity(Qt3DCore::QEntity *newLightEntity);

    Qt3DRender::QPointLight * getLight() const;
    void setLight(Qt3DRender::QPointLight *newLight);

    Qt3DCore::QEntity * rootEntity;

protected:
    void wheelEvent(QWheelEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void centerMesh();

private:
    Mesh *mesh;
    Qt3DRender::QCamera *m_camera;
    QWidget *m_container;
    Qt3DCore::QEntity *lightEntity;
    Qt3DRender::QPointLight *light;
};

#endif // VIEW3D_H
