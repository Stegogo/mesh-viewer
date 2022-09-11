#include "camcontroller.h"
#include <QDebug>
#include <Qt3DInput/QMouseHandler>

CamController::CamController(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
{
    m_keyUpPressed = false;
    m_keyDownPressed = false;
    m_keyLeftPressed = false;
    m_keyRightPressed = false;

    m_leftMousePressed = false;
    m_rightMousePressed = false;
    m_wheelInRoll = false;
    m_wheelOutRoll = false;

    m_dX = 0;
    m_dY = 0;
    m_zoom = 20;
    m_lookSpeed = 900;
    m_linearSpeed = 100;
    m_camera = nullptr;

    m_mouseDevice = new Qt3DInput::QMouseDevice(this);
    m_keyboardDevice = new Qt3DInput::QKeyboardDevice(this);
    m_logicalDevice = new Qt3DInput::QLogicalDevice(this);

    m_keyUpAction = new Qt3DInput::QAction(this);
    m_keyDownAction = new Qt3DInput::QAction(this);
    m_keyLeftAction = new Qt3DInput::QAction(this);
    m_keyRightAction = new Qt3DInput::QAction(this);
    m_leftMouseAction = new Qt3DInput::QAction(this);
    m_rightMouseAction = new Qt3DInput::QAction(this);
    m_wheelInAction = new Qt3DInput::QAction(this);
    m_wheelOutAction = new Qt3DInput::QAction(this);

    m_keyUpInput = new Qt3DInput::QActionInput(this);
    m_keyDownInput = new Qt3DInput::QActionInput(this);
    m_keyLeftInput = new Qt3DInput::QActionInput(this);
    m_keyRightInput = new Qt3DInput::QActionInput(this);
    m_leftMouseInput = new Qt3DInput::QActionInput(this);
    m_rightMouseInput = new Qt3DInput::QActionInput(this);
    m_wheelInInput = new Qt3DInput::QActionInput(this);
    m_wheelOutInput = new Qt3DInput::QActionInput(this);

    m_xAxis = new Qt3DInput::QAxis(this);
    m_yAxis = new Qt3DInput::QAxis(this);
    m_mouseXInput = new Qt3DInput::QAnalogAxisInput(this);
    m_mouseYInput = new Qt3DInput::QAnalogAxisInput(this);

    m_frameAction = new Qt3DLogic::QFrameAction(this);

    //-------------------MAPPING CONTROLS-------------------

    //-------------------ARROW KEYS

    // Setting up key UP action (W or ARROW UP)
    m_keyUpInput->setButtons(QVector<int>() << Qt::Key_Up << Qt::Key_W);
    m_keyUpInput->setSourceDevice(m_keyboardDevice);
    m_keyUpAction->addInput(m_keyUpInput);
    m_keyUpAction->setObjectName("Up_Key");

    // Setting up key DOWN action (S or ARROW DOWN)
    m_keyDownInput->setButtons(QVector<int>() << Qt::Key_Down << Qt::Key_S);
    m_keyDownInput->setSourceDevice(m_keyboardDevice);
    m_keyDownAction->addInput(m_keyDownInput);
    m_keyDownAction->setObjectName("Down_Key");

    // Setting up key LEFT action (A or ARROW LEFT)
    m_keyLeftInput->setButtons(QVector<int>() << Qt::Key_Left << Qt::Key_A);
    m_keyLeftInput->setSourceDevice(m_keyboardDevice);
    m_keyLeftAction->addInput(m_keyLeftInput);
    m_keyLeftAction->setObjectName("Left_Key");

    // Setting up key RIGHT action (D or ARROW RIGHT)
    m_keyRightInput->setButtons(QVector<int>() << Qt::Key_Right << Qt::Key_D);
    m_keyRightInput->setSourceDevice(m_keyboardDevice);
    m_keyRightAction->addInput(m_keyRightInput);
    m_keyRightAction->setObjectName("Right_Key");

    //-------------------MOUSE INPUT

    // Setting up LMB action
    m_leftMouseInput->setButtons(QVector<int>() << Qt::LeftButton);
    m_leftMouseInput->setSourceDevice(m_mouseDevice);
    m_leftMouseAction->addInput(m_leftMouseInput);
    m_leftMouseAction->setObjectName("Mouse_Left");

    // Setting up LMB action
    m_rightMouseInput->setButtons(QVector<int>() << Qt::RightButton);
    m_rightMouseInput->setSourceDevice(m_mouseDevice);
    m_rightMouseAction->addInput(m_rightMouseInput);
    m_rightMouseAction->setObjectName("Mouse_Right");

    //!==============REQUIRES REFACTOR========================
    // Setting up mouse wheel action ZOOM IN
    m_wheelInInput->setButtons(QVector<int>() << Qt::Key_Equal);
    m_wheelInInput->setSourceDevice(m_keyboardDevice);
    m_wheelInAction->addInput(m_wheelInInput);
    m_wheelInAction->setObjectName("Wheel_In");

    // Setting up mouse wheel action ZOOM OUT
    m_wheelOutInput->setButtons(QVector<int>() << Qt::Key_Minus);
    m_wheelOutInput->setSourceDevice(m_keyboardDevice);
    m_wheelOutAction->addInput(m_wheelOutInput);
    m_wheelOutAction->setObjectName("Wheel_Out");
    //!========================================================

    // Setting X input
    m_mouseXInput->setAxis(Qt3DInput::QMouseDevice::X);
    m_mouseXInput->setSourceDevice(m_mouseDevice);
    m_xAxis->addInput(m_mouseXInput);
    m_xAxis->setObjectName("X_Axis");

    // Setting Y input
    m_mouseYInput->setAxis(Qt3DInput::QMouseDevice::Y);
    m_mouseYInput->setSourceDevice(m_mouseDevice);
    m_yAxis->addInput(m_mouseYInput);
    m_yAxis->setObjectName("Y_Axis");

    //-------------------ADDING ACTIONS
    m_logicalDevice->addAction(m_keyUpAction);
    m_logicalDevice->addAction(m_keyDownAction);
    m_logicalDevice->addAction(m_keyLeftAction);
    m_logicalDevice->addAction(m_keyRightAction);
    m_logicalDevice->addAction(m_leftMouseAction);
    m_logicalDevice->addAction(m_rightMouseAction);
    m_logicalDevice->addAction(m_wheelInAction);
    m_logicalDevice->addAction(m_wheelOutAction);
    m_logicalDevice->addAxis(m_xAxis);
    m_logicalDevice->addAxis(m_yAxis);

    //-------------------CONNECTING SLOTS
    connect(m_keyUpAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(m_keyDownAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(m_keyLeftAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(m_keyRightAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(m_leftMouseAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(m_rightMouseAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(m_wheelInAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(m_wheelOutAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(m_xAxis, SIGNAL(valueChanged(float)), this, SLOT(axisValueChanged(float)));
    connect(m_yAxis, SIGNAL(valueChanged(float)), this, SLOT(axisValueChanged(float)));
    connect(m_frameAction, SIGNAL(triggered(float)), this, SLOT(frameActionTriggered(float)));

}

void CamController::setCamera(Qt3DRender::QCamera *newCamera)
{
    m_camera = newCamera;
}

float CamController::linearSpeed() const
{
    return m_linearSpeed;
}

void CamController::setLinearSpeed(float newLinearSpeed)
{
    m_linearSpeed = newLinearSpeed;
}

float CamController::lookSpeed() const
{
    return m_lookSpeed;
}

void CamController::setLookSpeed(float newLookSpeed)
{
    m_lookSpeed = newLookSpeed;
}

void CamController::activeChanged(bool isActive)
{
    if(sender()->objectName() == "Up_Key")
        m_keyUpPressed = isActive;
    if(sender()->objectName() == "Down_Key")
        m_keyDownPressed = isActive;
    if(sender()->objectName() == "Left_Key")
        m_keyLeftPressed = isActive;
    if(sender()->objectName() == "Right_Key")
        m_keyRightPressed = isActive;
    if (sender()->objectName() == "Mouse_Left")
        m_leftMousePressed = isActive;
    if (sender()->objectName() == "Mouse_Right")
        m_rightMousePressed = isActive;
    if (sender()->objectName() == "Wheel_In")
        m_wheelInRoll = isActive;
    if (sender()->objectName() == "Wheel_Out")
        m_wheelOutRoll = isActive;

}

void CamController::axisValueChanged(float value)
{
    if(sender()->objectName() == "X_Axis")
        m_dX = value;
    else if (sender()->objectName() == "Y_Axis")
        m_dY = value;
}


void CamController::frameActionTriggered(float dt)
{
    if(m_camera == nullptr)
        return;
    if (m_leftMousePressed)
    {
        m_camera->panAboutViewCenter(-m_dX * m_lookSpeed * dt);
        m_camera->tiltAboutViewCenter(-m_dY * m_lookSpeed * dt);
    }
    if (m_rightMousePressed)
    {
//        m_camera->pan((-m_dX * m_lookSpeed * dt) / 300);
//        m_camera->tilt((-m_dY * m_lookSpeed * dt) / 300);
         m_camera->viewAll();
    }
    if (m_keyUpPressed)
        m_camera->tiltAboutViewCenter(0.5 * m_lookSpeed * dt);
    if (m_keyDownPressed)
        m_camera->tiltAboutViewCenter(-0.5 * m_lookSpeed * dt);
    if (m_keyLeftPressed)
        m_camera->panAboutViewCenter(-0.5 * m_lookSpeed * dt);
    if (m_keyRightPressed)
        m_camera->panAboutViewCenter(0.5 * m_lookSpeed * dt);
}
