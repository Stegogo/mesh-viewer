#include "camcontroller.h"

//-----------------------------------------
// Constructor
CamController::CamController(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
{
    m_keyUpPressed = false;
    m_keyDownPressed = false;
    m_keyLeftPressed = false;
    m_keyRightPressed = false;

    m_leftMousePressed = false;
    m_rightMousePressed = false;

    m_dX = 0;
    m_dY = 0;
    m_zoom = 20;
    lookSpeed = 900;
    m_linearSpeed = 100;
    camera = nullptr;

    mouseDevice = new Qt3DInput::QMouseDevice(this);
    keyboardDevice = new Qt3DInput::QKeyboardDevice(this);
    logicalDevice = new Qt3DInput::QLogicalDevice(this);

    keyUpAction = new Qt3DInput::QAction(this);
    keyDownAction = new Qt3DInput::QAction(this);
    keyLeftAction = new Qt3DInput::QAction(this);
    keyRightAction = new Qt3DInput::QAction(this);
    leftMouseAction = new Qt3DInput::QAction(this);
    rightMouseAction = new Qt3DInput::QAction(this);

    keyUpInput = new Qt3DInput::QActionInput(this);
    keyDownInput = new Qt3DInput::QActionInput(this);
    keyLeftInput = new Qt3DInput::QActionInput(this);
    keyRightInput = new Qt3DInput::QActionInput(this);
    leftMouseInput = new Qt3DInput::QActionInput(this);
    rightMouseInput = new Qt3DInput::QActionInput(this);

    xAxis = new Qt3DInput::QAxis(this);
    yAxis = new Qt3DInput::QAxis(this);
    mouseXInput = new Qt3DInput::QAnalogAxisInput(this);
    mouseYInput = new Qt3DInput::QAnalogAxisInput(this);

    frameAction = new Qt3DLogic::QFrameAction(this);

    //-------------------MAPPING CONTROLS-------------------

    //-------------------ARROW KEYS

    // Setting up key UP action (W or ARROW UP)
    keyUpInput->setButtons(QVector<int>() << Qt::Key_Up << Qt::Key_W);
    keyUpInput->setSourceDevice(keyboardDevice);
    keyUpAction->addInput(keyUpInput);
    keyUpAction->setObjectName("Up_Key");

    // Setting up key DOWN action (S or ARROW DOWN)
    keyDownInput->setButtons(QVector<int>() << Qt::Key_Down << Qt::Key_S);
    keyDownInput->setSourceDevice(keyboardDevice);
    keyDownAction->addInput(keyDownInput);
    keyDownAction->setObjectName("Down_Key");

    // Setting up key LEFT action (A or ARROW LEFT)
    keyLeftInput->setButtons(QVector<int>() << Qt::Key_Left << Qt::Key_A);
    keyLeftInput->setSourceDevice(keyboardDevice);
    keyLeftAction->addInput(keyLeftInput);
    keyLeftAction->setObjectName("Left_Key");

    // Setting up key RIGHT action (D or ARROW RIGHT)
    keyRightInput->setButtons(QVector<int>() << Qt::Key_Right << Qt::Key_D);
    keyRightInput->setSourceDevice(keyboardDevice);
    keyRightAction->addInput(keyRightInput);
    keyRightAction->setObjectName("Right_Key");

    //-------------------MOUSE INPUT

    // Setting up LMB action
    leftMouseInput->setButtons(QVector<int>() << Qt::LeftButton);
    leftMouseInput->setSourceDevice(mouseDevice);
    leftMouseAction->addInput(leftMouseInput);
    leftMouseAction->setObjectName("Mouse_Left");

    // Setting up LMB action
    rightMouseInput->setButtons(QVector<int>() << Qt::RightButton);
    rightMouseInput->setSourceDevice(mouseDevice);
    rightMouseAction->addInput(rightMouseInput);
    rightMouseAction->setObjectName("Mouse_Right");

    // Setting X input
    mouseXInput->setAxis(Qt3DInput::QMouseDevice::X);
    mouseXInput->setSourceDevice(mouseDevice);
    xAxis->addInput(mouseXInput);
    xAxis->setObjectName("X_Axis");

    // Setting Y input
    mouseYInput->setAxis(Qt3DInput::QMouseDevice::Y);
    mouseYInput->setSourceDevice(mouseDevice);
    yAxis->addInput(mouseYInput);
    yAxis->setObjectName("Y_Axis");

    //-------------------ADDING ACTIONS
    logicalDevice->addAction(keyUpAction);
    logicalDevice->addAction(keyDownAction);
    logicalDevice->addAction(keyLeftAction);
    logicalDevice->addAction(keyRightAction);
    logicalDevice->addAction(leftMouseAction);
    logicalDevice->addAction(rightMouseAction);
    logicalDevice->addAxis(xAxis);
    logicalDevice->addAxis(yAxis);

    // Connecting slots
    connect(keyUpAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(keyDownAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(keyLeftAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(keyRightAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(leftMouseAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(rightMouseAction, SIGNAL(activeChanged(bool)), this, SLOT(activeChanged(bool)));
    connect(xAxis, SIGNAL(valueChanged(float)), this, SLOT(axisValueChanged(float)));
    connect(yAxis, SIGNAL(valueChanged(float)), this, SLOT(axisValueChanged(float)));
    connect(frameAction, SIGNAL(triggered(float)), this, SLOT(frameActionTriggered(float)));

}

//-----------------------------------------
// Setter for camera
void CamController::setCamera(Qt3DRender::QCamera *newCamera)
{
    camera = newCamera;
}

//-----------------------------------------
// Getter for linear speed
float CamController::getLinearSpeed() const
{
    return m_linearSpeed;
}

//-----------------------------------------
// Setter for linear speed
void CamController::setLinearSpeed(float newLinearSpeed)
{
    m_linearSpeed = newLinearSpeed;
}

//-----------------------------------------
// Getter for look speed
float CamController::getLookSpeed() const
{
    return lookSpeed;
}

//-----------------------------------------
// Setter for look speed
void CamController::setLookSpeed(float newLookSpeed)
{
    lookSpeed = newLookSpeed;
}

//-----------------------------------------
// Toggle key states pressed/unpressed
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

}

//-----------------------------------------
// Tracker for axes values
void CamController::axisValueChanged(float value)
{
    if(sender()->objectName() == "X_Axis")
        m_dX = value;
    else if (sender()->objectName() == "Y_Axis")
        m_dY = value;
}

//-----------------------------------------
// Key bounds
void CamController::frameActionTriggered(float dt)
{
    if(camera == nullptr)
        return;
    if (m_leftMousePressed)
    {
        camera->panAboutViewCenter(-m_dX * lookSpeed * dt);
        camera->tiltAboutViewCenter(-m_dY * lookSpeed * dt);
    }
    if (m_rightMousePressed)
    {
        // REQUIRES REFACTOR
        camera->viewAll();
    }
    if (m_keyUpPressed)
        camera->tiltAboutViewCenter(0.5 * lookSpeed * dt);
    if (m_keyDownPressed)
        camera->tiltAboutViewCenter(-0.5 * lookSpeed * dt);
    if (m_keyLeftPressed)
        camera->panAboutViewCenter(-0.5 * lookSpeed * dt);
    if (m_keyRightPressed)
        camera->panAboutViewCenter(0.5 * lookSpeed * dt);
}
