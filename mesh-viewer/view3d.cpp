#include "view3d.h"

//-----------------------------------------
// Constructor
View3D::View3D()
{
    m_camera = nullptr;
    m_container = nullptr;
    rootEntity = new Qt3DCore::QEntity();
    mesh = new Mesh();
    lightEntity = nullptr;
    light = nullptr;

}

//-----------------------------------------
// Setter for camera & light bound to it
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
}

//-----------------------------------------
// Wheel event
void View3D::wheelEvent(QWheelEvent* event)
{
    if(m_camera->fieldOfView() >= 0.1)
        m_camera->setFieldOfView(m_camera->fieldOfView() - event->delta() / 300.f);
    else
        m_camera->setFieldOfView(0.1);
}

//-----------------------------------------
// Center mesh on screen
// REQUIRES REFACTOR
void View3D::centerMesh()
{
    // Center of the 3D Widget = (widgetWidth/2, widgetHeight/2)
    QVector3D position(m_container->width() / 2, m_container->height()/2, 0);
    mesh->transform->rotateAround(position, 0, QVector3D(0, 0, 0));
}

//-----------------------------------------
// Getter for camera
Qt3DRender::QCamera *View3D::getCamera()
{
    return m_camera;
}

//-----------------------------------------
// Setter for widget
void View3D::setWidget(QWidget *newContainer)
{
    m_container = newContainer;
}

//-----------------------------------------
// Getter for mesh
Mesh *View3D::getMesh() const
{
    return mesh;
}

//-----------------------------------------
// Setter for camera
void View3D::setMesh(Mesh *newMesh)
{
    mesh = newMesh;
}

//-----------------------------------------
// Getter for light
Qt3DRender::QPointLight *View3D::getLight() const
{
    return light;
}

//-----------------------------------------
// Setter for light
void View3D::setLight(Qt3DRender::QPointLight *newLight)
{
    light = newLight;
}

//-----------------------------------------
// Getter for light entity
Qt3DCore::QEntity *View3D::getLightEntity() const
{
    return lightEntity;
}

//-----------------------------------------
// Setter for light entity
void View3D::setLightEntity(Qt3DCore::QEntity *newLightEntity)
{
    lightEntity = newLightEntity;
}
