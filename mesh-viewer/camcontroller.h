#ifndef CAMCONTROLLER_H
#define CAMCONTROLLER_H

#include <Qt3DInput/QMouseDevice>       // for registering mouse device
#include <Qt3DInput/QKeyboardDevice>    // for registering keyboard device
#include <Qt3DInput/QLogicalDevice>     // for registering logical device
#include <Qt3DInput/QAction>            // for registering actions
#include <Qt3DInput/QActionInput>       // action inputs
#include <Qt3DInput/QAxis>              // for defining axes
#include <Qt3DInput/QAnalogAxisInput>   // for detecting mouse input
#include <Qt3DRender/QCamera>           // for camera
#include <Qt3DLogic/QFrameAction>       // for binding keys to actions

//================================================
// CAM CONTROLLER CLASS
// Custom camera controller.
//================================================

class CamController : public Qt3DCore::QEntity
{
    Q_OBJECT

public:
    CamController(Qt3DCore::QNode *parent = Q_NULLPTR);

    float getLookSpeed() const;
    float getLinearSpeed() const;

    void setCamera(Qt3DRender::QCamera *newCamera);
    void setLookSpeed(float newLookSpeed);
    void setLinearSpeed(float newLinearSpeed);

protected slots:
    void activeChanged(bool isActive);
    void axisValueChanged(float value);
    void frameActionTriggered(float dt);

private:
    Qt3DInput::QMouseDevice *mouseDevice;
    Qt3DInput::QKeyboardDevice *keyboardDevice;
    Qt3DInput::QLogicalDevice *logicalDevice;

    Qt3DInput::QAction *keyUpAction;
    Qt3DInput::QAction *keyDownAction;
    Qt3DInput::QAction *keyLeftAction;
    Qt3DInput::QAction *keyRightAction;
    Qt3DInput::QAction *leftMouseAction;
    Qt3DInput::QAction *rightMouseAction;

    Qt3DInput::QActionInput *keyUpInput;
    Qt3DInput::QActionInput *keyDownInput;
    Qt3DInput::QActionInput *keyLeftInput;
    Qt3DInput::QActionInput *keyRightInput;
    Qt3DInput::QActionInput *leftMouseInput;
    Qt3DInput::QActionInput *rightMouseInput;

    Qt3DInput::QAxis *xAxis;
    Qt3DInput::QAxis *yAxis;

    Qt3DInput::QAnalogAxisInput *mouseXInput;
    Qt3DInput::QAnalogAxisInput *mouseYInput;

    Qt3DLogic::QFrameAction *frameAction;

    Qt3DRender::QCamera *camera;

    float lookSpeed;
    float m_linearSpeed;
    float m_dX;
    float m_dY;
    float m_zoom;

    bool m_keyUpPressed;
    bool m_keyDownPressed;
    bool m_keyLeftPressed;
    bool m_keyRightPressed;
    bool m_leftMousePressed;
    bool m_rightMousePressed;

};

#endif // CAMCONTROLLER_H
