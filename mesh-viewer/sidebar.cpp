#include "sidebar.h"
#include "section.h"

#include <QLabel>
#include <QColorDialog>
#include <Qt3DRender/QParameter>
#include <QDebug>
#include <QPalette>
#include <QSlider>

#include <Qt3DRender/QEffect>
#include <Qt3DRender/QMaterial>

Sidebar::Sidebar(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout();

    lightColor = Qt::white;
    diffuseColor = Qt::white;
    ambientColor = Qt::white;
    specularColor = Qt::white;
    wireframeColor = Qt::white;

    Section *geometrySection = new Section("Scene", 300, this);
    auto *geomLayout = new QVBoxLayout();

    // Light mode select section
    auto *lightModeLayout = new QHBoxLayout();
    geomLayout->addWidget(new QLabel("Shading mode", geometrySection));

    // Set up light mode buttons
    shadeFlatButton = new QPushButton("Flat");
    shadeFlatButton->setCheckable(true);
    lightModeLayout->addWidget(shadeFlatButton);

    shadeSmoothButton = new QPushButton("Smooth");
    shadeSmoothButton->setCheckable(true);
    shadeSmoothButton->setChecked(true);
    lightModeLayout->addWidget(shadeSmoothButton);

    geomLayout->addLayout(lightModeLayout);

    // Light intensity slider
    geomLayout->addWidget(new QLabel("Light intensity", geometrySection));
    sliderLight = new QSlider(Qt::Horizontal , this);
    geomLayout->addWidget(sliderLight);
    sliderLight->setMinimum(0);
    sliderLight->setMaximum(10);
    sliderLight->setSingleStep(1);
    sliderLight->setSliderPosition(8);
    connect(sliderLight, &QSlider::valueChanged, this, &Sidebar::setLightIntensity);

    // Light intensity slider
    geomLayout->addWidget(new QLabel("Line width", geometrySection));
    sliderLine = new QSlider(Qt::Horizontal , this);
    geomLayout->addWidget(sliderLine);
    sliderLine->setMinimum(0);
    sliderLine->setMaximum(20);
    sliderLine->setSingleStep(1);
    sliderLine->setSliderPosition(10);
    connect(sliderLine, &QSlider::valueChanged, this, &Sidebar::setLineWidth);

    geometrySection->setContentLayout(*geomLayout);

    // Attach actions
    connect(shadeFlatButton, SIGNAL(clicked()), this, SLOT(pickLightMode()));
    connect(shadeSmoothButton, SIGNAL(clicked()), this, SLOT(pickLightMode()));

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

    // Setting up specular color picker:
    auto *specularLayout = new QHBoxLayout();
    specularLayout->addWidget(new QLabel("Specular"));
    // Adjust the button
    specularColorButton = new QPushButton(" ");
    specularPallete = specularColorButton->palette();
    specularPallete.setColor(QPalette::Button, specularColor);
    specularColorButton->setAutoFillBackground(true);
    specularColorButton->setFlat(true);
    specularColorButton->setPalette(specularPallete);
    specularColorButton->update();
    specularLayout->addWidget(specularColorButton);
    viewLayout->addLayout(specularLayout);

    // Setting up wireframe color picker:
    auto *wireframeLayout = new QHBoxLayout();
    wireframeLayout->addWidget(new QLabel("Wireframe"));
    // Adjust the button
    wireframeColorButton = new QPushButton(" ");
    wireframePallete = wireframeColorButton->palette();
    wireframePallete.setColor(QPalette::Button, wireframeColor);
    wireframeColorButton->setAutoFillBackground(true);
    wireframeColorButton->setFlat(true);
    wireframeColorButton->setPalette(wireframePallete);
    wireframeColorButton->update();
    wireframeLayout->addWidget(wireframeColorButton);
    viewLayout->addLayout(wireframeLayout);

    // Attach color picker
    connect(lightColorButton, SIGNAL(clicked()), this, SLOT(pickColor()));
    connect(diffuseColorButton, SIGNAL(clicked()), this, SLOT(pickColor()));
    connect(ambientColorButton, SIGNAL(clicked()), this, SLOT(pickColor()));
    connect(specularColorButton, SIGNAL(clicked()), this, SLOT(pickColor()));
    connect(wireframeColorButton, SIGNAL(clicked()), this, SLOT(pickColor()));
    viewSection->setContentLayout(*viewLayout);

    logger = new QListWidget();

    m_layout->addWidget(geometrySection);
    m_layout->addWidget(viewSection);
    m_layout->addWidget(logger);
    setLayout(m_layout);

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
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

        // Update ambient color
        mesh->light->setColor(lightColor);
        mesh->lightColor->setValue(lightColor);

    }
    else if (QObject::sender() == diffuseColorButton)
    {
        diffuseColor = newColor;
        diffusePallete.setColor(QPalette::Button, diffuseColor);
        diffuseColorButton->setAutoFillBackground(true);
        diffuseColorButton->setFlat(true);
        diffuseColorButton->setPalette(diffusePallete);
        diffuseColorButton->update();

        // Update diffuse color
        mesh->kd->setValue(diffuseColor);

    }
    else if (QObject::sender() == ambientColorButton)
    {
        ambientColor = newColor;
        ambientPallete.setColor(QPalette::Button, ambientColor);
        ambientColorButton->setAutoFillBackground(true);
        ambientColorButton->setFlat(true);
        ambientColorButton->setPalette(ambientPallete);
        ambientColorButton->update();

        // Update ambient color
        mesh->ka->setValue(ambientColor);
    }
    else if (QObject::sender() == specularColorButton)
    {
        specularColor = newColor;
        specularPallete.setColor(QPalette::Button, specularColor);
        specularColorButton->setAutoFillBackground(true);
        specularColorButton->setFlat(true);
        specularColorButton->setPalette(specularPallete);
        specularColorButton->update();

        // Update specular color
        mesh->ks->setValue(specularColor);
    }
    else if (QObject::sender() == wireframeColorButton)
    {
        wireframeColor = newColor;
        wireframePallete.setColor(QPalette::Button, wireframeColor);
        wireframeColorButton->setAutoFillBackground(true);
        wireframeColorButton->setFlat(true);
        wireframeColorButton->setPalette(wireframePallete);
        wireframeColorButton->update();

        // Update ambient color
        mesh->lineColor->setValue(wireframeColor);
    }
    else
        return;
}

//---------------------------
// Picking and updating lighting modes
void Sidebar::pickLightMode()
{
    if (QObject::sender() == shadeFlatButton)
    {
        // Set flat shading
        mesh->glShader->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/wireframeFlat.vert"))));
        shadeSmoothButton->setChecked(false);
        shadeFlatButton->setChecked(true);
    }
    if (QObject::sender() == shadeSmoothButton)
    {
        // Set smooth shading
        mesh->glShader->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/wireframe.vert"))));
        shadeSmoothButton->setChecked(true);
        shadeFlatButton->setChecked(false);
    }
}

void Sidebar::setLightIntensity()
{
    auto value = (float)sliderLight->value()/10;
    mesh->light->setIntensity(value);
    mesh->lightIntensity->setValue(QVector3D( value, value, value ));
}

void Sidebar::setLineWidth()
{
    auto value = (float)sliderLine->value()/10;
    mesh->lineWidth->setValue(value);
}

const QColor &Sidebar::getSpecularColor() const
{
    return specularColor;
}

const QColor &Sidebar::getWireframeColor() const
{
    return wireframeColor;
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
}
