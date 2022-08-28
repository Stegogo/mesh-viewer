#ifndef VIEW3D_H
#define VIEW3D_H

#include <QWidget>
#include <Qt3DExtras/Qt3DWindow>
#include <QDebug>
#include <QtCore/QEvent>
#include <QPainter>
#include <QWheelEvent>
#include <Qt3DCore/QTransform>
#include <QCameraFocus>

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
    void setWidget(QWidget *newContainer);
protected:
    void wheelEvent(QWheelEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private:
    Qt3DRender::QCamera *m_camera;
    QWidget *m_container;
    QCameraFocus *focus;

};

#endif // VIEW3D_H
