#include "view3d.h"
#include <Qt3DRender/QCamera>
#include <QCamera>
#include <QDebug>


View3D::View3D()
{
    m_camera = nullptr;
    m_container = nullptr;
    focus = nullptr;

    mesh = new Mesh();

    lightEntity = nullptr;
    light = nullptr;

}
void View3D::setCamera(Qt3DRender::QCamera *newCamera)
{
    m_camera = newCamera;

    // Setting light

    lightEntity = new Qt3DCore::QEntity(m_camera);

    light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(0.8f);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(0, 0, 40.0f));
    lightEntity->addComponent(lightTransform);

    mesh->setLight(light);

    m_camera->viewAll();

    //connect(mesh->meshEntity, &Qt3DRender::QMesh::sourceChanged, this, &View3D::resetFOV);

}

Qt3DRender::QCamera *View3D::getCamera()
{
    return m_camera;
}

void View3D::setWidget(QWidget *newContainer)
{
    m_container = newContainer;
}
void View3D::wheelEvent(QWheelEvent* event)
{
    m_camera->setFieldOfView(m_camera->fieldOfView() - event->delta() / 300.f);

}

Mesh *View3D::getMesh() const
{
    return mesh;
}

void View3D::setMesh(Mesh *newMesh)
{
    mesh = newMesh;
}

void View3D::resetFOV()
{
    m_camera->viewAll();
}

Qt3DRender::QPointLight *View3D::getLight() const
{
    return light;
}

void View3D::setLight(Qt3DRender::QPointLight *newLight)
{
    light = newLight;
}

Qt3DCore::QEntity *View3D::getLightEntity() const
{
    return lightEntity;
}

void View3D::setLightEntity(Qt3DCore::QEntity *newLightEntity)
{
    lightEntity = newLightEntity;
}
