#ifndef VIEW3D_H
#define VIEW3D_H

#include "mesh.h"
#include <QWidget>
#include <Qt3DExtras/Qt3DWindow>
#include <QDebug>
#include <QtCore/QEvent>
#include <QPainter>
#include <QWheelEvent>
#include <Qt3DCore/QTransform>
#include <QCameraFocus>
#include <Qt3DRender/QPointLight>

//================================================
// VIEW 3D CLASS
// Manages events for 3D window, e.g. wheelEvent.
//================================================


class View3D : public Qt3DExtras::Qt3DWindow
{
    Q_OBJECT
public:
    View3D();
    void setCamera(Qt3DRender::QCamera *newCamera);
    Qt3DRender::QCamera *getCamera();
    void setWidget(QWidget *newContainer);

    Mesh *getMesh() const;
    void setMesh(Mesh *newMesh);
protected:
    void wheelEvent(QWheelEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
protected slots:
    void resetFOV();
private:
    Mesh *mesh;
    Qt3DRender::QCamera *m_camera;
    QWidget *m_container;
    QCameraFocus *focus;
    Qt3DCore::QEntity *lightEntity;
    Qt3DRender::QPointLight *light;
};

#endif // VIEW3D_H
