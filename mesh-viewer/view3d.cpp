#include "view3d.h"
#include <Qt3DRender/QCamera>
#include <QCamera>
#include <QDebug>


View3D::View3D()
{
    m_camera = nullptr;
    m_container = nullptr;
    focus = nullptr;
}
void View3D::setCamera(Qt3DRender::QCamera *newCamera)
{
    m_camera = newCamera;

}
void View3D::setWidget(QWidget *newContainer)
{
    m_container = newContainer;
}
void View3D::wheelEvent(QWheelEvent* event)
{
    QVector3D camPos = m_camera->position();
    //camPos.normalize();
    camPos = m_camera->position() + QVector3D(0, 0, event->delta() / 200.f);
    m_camera->setPosition(camPos);
    qDebug() << m_camera->position();



}
