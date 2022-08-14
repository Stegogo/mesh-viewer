#ifndef VIEW3D_H
#define VIEW3D_H

#include <QWidget>
#include <Qt3DExtras/Qt3DWindow>
#include <QDebug>
#include <QtCore/QEvent>
#include <QPainter>
#include <QWheelEvent>

class View3D : public Qt3DExtras::Qt3DWindow
{
    Q_OBJECT
public:
    View3D();
    void setCamera(Qt3DRender::QCamera *newCamera);
protected:
    void wheelEvent(QWheelEvent *event);
private:
    Qt3DRender::QCamera *m_camera;
};

#endif // VIEW3D_H
