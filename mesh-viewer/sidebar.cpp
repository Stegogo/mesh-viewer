#include "sidebar.h"
#include "section.h"

#include <QLabel>

#include <QColorDialog>

#include <QDebug>
#include <QPalette>
#include <QSlider>

Sidebar::Sidebar(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout();

    lightColor = Qt::white;
    diffuseColor = Qt::white;
    ambientColor = Qt::white;

    Section *geometrySection = new Section("Scene", 300, this);
    auto *geomLayout = new QVBoxLayout();

    // Light mode select section
    auto *lightModeLayout = new QHBoxLayout();
    geomLayout->addWidget(new QLabel("Light mode", geometrySection));

    // Set up light mode buttons
    lightAsIsButton = new QPushButton("As-is");
    lightModeLayout->addWidget(lightAsIsButton);
    lightFollowCameraButton = new QPushButton("Camera");
    lightModeLayout->addWidget(lightFollowCameraButton);
    lightFollowCameraButton->setDown(true);

    geomLayout->addLayout(lightModeLayout);

    // Light intensity slider
    geomLayout->addWidget(new QLabel("Light intensity", geometrySection));
    slider = new QSlider(Qt::Horizontal , this);
    geomLayout->addWidget(slider);
    slider->setMinimum(0);
    slider->setMaximum(10);
    slider->setSingleStep(1);
    slider->setSliderPosition(8);

    QLabel * label = new QLabel("8", this);
    geomLayout->addWidget(label);
    connect(slider, &QSlider::valueChanged, label, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
    connect(slider, &QSlider::valueChanged, this, &Sidebar::setLightIntensity);

    geometrySection->setContentLayout(*geomLayout);

    // Attach actions
    connect(lightAsIsButton, SIGNAL(clicked()), this, SLOT(pickLightMode()));
    connect(lightFollowCameraButton, SIGNAL(clicked()), this, SLOT(pickLightMode()));

    //---------------------------

    Section *viewSection = new Section("Mesh", 300, this);
    auto *viewLayout = new QVBoxLayout();
    viewLayout->addWidget(new QLabel("Adjust colors", viewSection));

    // Setting up light color picker:
    auto *lightLayout = new QHBoxLayout();
    lightLayout->addWidget(new QLabel("Light"));
    // Adjust the button
    lightColorButton = new QPushButton(" ");

    lightPallete = lightColorButton->palette();
    lightPallete.setColor(QPalette::Button, lightColor);
    lightColorButton->setAutoFillBackground(true);
    lightColorButton->setFlat(true);
    lightColorButton->setPalette(lightPallete);
    lightColorButton->update();
    lightLayout->addWidget(lightColorButton);
    viewLayout->addLayout(lightLayout);

    // Setting up diffuse color picker:
    auto *diffuseLayout = new QHBoxLayout();
    diffuseLayout->addWidget(new QLabel("Diffuse"));
    // Adjust the button
    diffuseColorButton = new QPushButton(" ");
    diffusePallete = diffuseColorButton->palette();
    diffusePallete.setColor(QPalette::Button, diffuseColor);
    diffuseColorButton->setAutoFillBackground(true);
    diffuseColorButton->setFlat(true);
    diffuseColorButton->setPalette(diffusePallete);
    diffuseColorButton->update();
    diffuseLayout->addWidget(diffuseColorButton);
    viewLayout->addLayout(diffuseLayout);

    // Setting up ambient color picker:
    auto *ambientLayout = new QHBoxLayout();
    ambientLayout->addWidget(new QLabel("Ambient"));
    // Adjust the button
    ambientColorButton = new QPushButton(" ");
    ambientPallete = ambientColorButton->palette();
    ambientPallete.setColor(QPalette::Button, ambientColor);
    ambientColorButton->setAutoFillBackground(true);
    ambientColorButton->setFlat(true);
    ambientColorButton->setPalette(ambientPallete);
    ambientColorButton->update();
    ambientLayout->addWidget(ambientColorButton);
    viewLayout->addLayout(ambientLayout);

    // Attach color picker
    connect(lightColorButton, SIGNAL(clicked()), this, SLOT(pickColor()));
    connect(diffuseColorButton, SIGNAL(clicked()), this, SLOT(pickColor()));
    connect(ambientColorButton, SIGNAL(clicked()), this, SLOT(pickColor()));
    viewSection->setContentLayout(*viewLayout);

    logger = new QListWidget();

    m_layout->addWidget(geometrySection);
    m_layout->addWidget(viewSection);
    m_layout->addWidget(logger);
    setLayout(m_layout);

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

const QColor &Sidebar::getLightColor() const
{
    return lightColor;
}
const QColor &Sidebar::getAmbientColor() const
{
    return ambientColor;
}

const QColor &Sidebar::getDiffuseColor() const
{
    return diffuseColor;
}

//---------------------------
// Picking and updating colors
void Sidebar::pickColor()
{
    QColor prevColor;
    if (QObject::sender() == lightColorButton)
        prevColor = lightColor;
    else if (QObject::sender() == diffuseColorButton)
        prevColor = diffuseColor;
    else if (QObject::sender() == ambientColorButton)
        prevColor = ambientColor;
    else
        prevColor = Qt::white;

    QColor newColor = QColorDialog::getColor(prevColor, parentWidget());

    if (QObject::sender() == lightColorButton)
    {
        lightColor = newColor;
        lightPallete.setColor(QPalette::Button, lightColor);
        lightColorButton->setAutoFillBackground(true);
        lightColorButton->setFlat(true);
        lightColorButton->setPalette(lightPallete);
        lightColorButton->update();

        mesh->light->setColor(lightColor);
    }
    else if (QObject::sender() == diffuseColorButton)
    {
        diffuseColor = newColor;
        diffusePallete.setColor(QPalette::Button, diffuseColor);
        diffuseColorButton->setAutoFillBackground(true);
        diffuseColorButton->setFlat(true);
        diffuseColorButton->setPalette(diffusePallete);
        diffuseColorButton->update();

        mesh->material->setDiffuse(diffuseColor);
    }
    else if (QObject::sender() == ambientColorButton)
    {
        ambientColor = newColor;
        ambientPallete.setColor(QPalette::Button, ambientColor);
        ambientColorButton->setAutoFillBackground(true);
        ambientColorButton->setFlat(true);
        ambientColorButton->setPalette(ambientPallete);
        ambientColorButton->update();

        mesh->material->setAmbient(ambientColor);
    }
    else
        return;
}

//---------------------------
// Picking and updating lighting modes
void Sidebar::pickLightMode()
{
    if (QObject::sender() == lightAsIsButton)
    {
        //Qt3DCore::QEntity * rootEntity = new Qt3DCore::QEntity;
        view->getLightEntity()->setParent(view->rootEntity);

        mesh->lightEntity = view->getLightEntity();
        mesh->setLight(view->getLight());
        view->getLight()->setColor(lightColor);
        lightFollowCameraButton->setDown(false);
        lightAsIsButton->setDown(true);
    }
    if (QObject::sender() == lightFollowCameraButton)
    {
        view->getLightEntity()->setParent((Qt3DCore::QEntity *)view->getCamera());
        mesh->setLight(view->getLight());
        lightFollowCameraButton->setDown(true);
        lightAsIsButton->setDown(false);
    }
}

void Sidebar::setLightIntensity()
{
    mesh->light->setIntensity((float)slider->value()/10);
    //view->getLight()->setIntensity((float)slider->value()/10);
}

void Sidebar::setView(View3D *newView)
{
    view = newView;
}


Mesh *Sidebar::getMesh() const
{
    return mesh;
}

void Sidebar::setMesh(Mesh *newMesh)
{
    mesh = newMesh;
//    connect(mesh->meshEntity, &Qt3DRender::QMesh::sourceChanged, this, &Sidebar::logMeshStatus);
}


