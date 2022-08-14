#include "view3d.h"
#include <Qt3DRender/QCamera>
#include <QDebug>

View3D::View3D()
{
    m_camera = nullptr;
    m_container = nullptr;
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
    camPos.normalize();
    camPos = m_camera->position() - QVector3D(0, 0, event->delta() / 200.f);
    m_camera->setPosition(camPos);
    qDebug() << m_camera->position();
}
//void View3D::paintEvent(QPaintEvent *e) {

//    Q_UNUSED(e);
//    qDebug() << "a";
//    QPainter qp(m_container);
//    drawLines(&qp);
//}

//void View3D::drawLines(QPainter *qp) {

//  QPen pen(Qt::black, 2, Qt::SolidLine);
//  qp->setPen(pen);
//  qp->drawLine(20, 40, 250, 40);

//  pen.setStyle(Qt::DashLine);
//  qp->setPen(pen);
//  qp->drawLine(20, 80, 250, 80);

//  pen.setStyle(Qt::DashDotLine);
//  qp->setPen(pen);
//  qp->drawLine(20, 120, 250, 120);

//  pen.setStyle(Qt::DotLine);
//  qp->setPen(pen);
//  qp->drawLine(20, 160, 250, 160);

//  pen.setStyle(Qt::DashDotDotLine);
//  qp->setPen(pen);
//  qp->drawLine(20, 200, 250, 200);

//  QVector<qreal> dashes;
//  qreal space = 4;

//  dashes << 1 << space << 5 << space;

//  pen.setStyle(Qt::CustomDashLine);
//  pen.setDashPattern(dashes);

//  qp->setPen(pen);
//  qp->drawLine(20, 240, 250, 240);
//}
