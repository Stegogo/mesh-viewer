#ifndef CAMCONTROLLER_H
#define CAMCONTROLLER_H

#include <Qt3DExtras/Qt3DWindow>
#include <QtWidgets/QWidget>
#include <Qt3DCore/QEntity>
#include <Qt3DInput/QMouseDevice>
#include <Qt3DInput/QKeyboardDevice>
#include <Qt3DInput/QLogicalDevice>
#include <Qt3DInput/QAction>
#include <Qt3DInput/QActionInput>
#include <Qt3DInput/QAxis>
#include <Qt3DInput/QAnalogAxisInput>
#include <Qt3DRender/QCamera>
#include <Qt3DLogic/QFrameAction>
#include <Qt3DInput/QWheelEvent>
#include <Qt3DInput/QMouseHandler>

class CamController : public Qt3DCore::QEntity
{
    Q_OBJECT

public:
    CamController(Qt3DCore::QNode *parent = Q_NULLPTR);

    void setCamera(Qt3DRender::QCamera *newCamera);

    float lookSpeed() const;
    float linearSpeed() const;

    void setLookSpeed(float newLookSpeed);
    void setLinearSpeed(float newLinearSpeed);

protected slots:
    void activeChanged(bool isActive);
    void axisValueChanged(float value);
    void frameActionTriggered(float dt);

private:
    Qt3DInput::QMouseDevice *m_mouseDevice;
    Qt3DInput::QKeyboardDevice *m_keyboardDevice;
    Qt3DInput::QLogicalDevice *m_logicalDevice;

    Qt3DInput::QAction *m_keyUpAction;
    Qt3DInput::QAction *m_keyDownAction;
    Qt3DInput::QAction *m_keyLeftAction;
    Qt3DInput::QAction *m_keyRightAction;
    Qt3DInput::QAction *m_leftMouseAction;
    Qt3DInput::QAction *m_wheelInAction;
    Qt3DInput::QAction *m_wheelOutAction;

    Qt3DInput::QActionInput *m_keyUpInput;
    Qt3DInput::QActionInput *m_keyDownInput;
    Qt3DInput::QActionInput *m_keyLeftInput;
    Qt3DInput::QActionInput *m_keyRightInput;
    Qt3DInput::QActionInput *m_leftMouseInput;
    Qt3DInput::QActionInput *m_wheelInInput;
    Qt3DInput::QActionInput *m_wheelOutInput;

    Qt3DInput::QAxis *m_xAxis;
    Qt3DInput::QAxis *m_yAxis;

    Qt3DInput::QAnalogAxisInput *m_mouseXInput;
    Qt3DInput::QAnalogAxisInput *m_mouseYInput;

    Qt3DLogic::QFrameAction *m_frameAction;

    Qt3DRender::QCamera *m_camera;

    float m_lookSpeed;
    float m_linearSpeed;
    float m_dX;
    float m_dY;
    float m_zoom;

    bool m_keyUpPressed;
    bool m_keyDownPressed;
    bool m_keyLeftPressed;
    bool m_keyRightPressed;
    bool m_leftMousePressed;
    bool m_wheelInRoll;
    bool m_wheelOutRoll;

};

#endif // CAMCONTROLLER_H
