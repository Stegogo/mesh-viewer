#include "sidebar.h"
#include "section.h"

#include <QLabel>

#include <QColorDialog>

#include <QDebug>
#include <QPalette>

Sidebar::Sidebar(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout();

    lightColor = Qt::white;
    diffuseColor = Qt::white;
    ambientColor = Qt::white;

    Section *geometrySection = new Section("Geometry", 300, this);
    auto *geomLayout = new QVBoxLayout();
    geomLayout->addWidget(new QLabel("Some Text in Section", geometrySection));
    geomLayout->addWidget(new QPushButton("Button in Section", geometrySection));
    geometrySection->setContentLayout(*geomLayout);

    Section *viewSection = new Section("View", 300, this);
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
    connect( lightColorButton, SIGNAL(clicked()), this, SLOT(pickColor()));
    connect( diffuseColorButton, SIGNAL(clicked()), this, SLOT(pickColor()));
    connect( ambientColorButton, SIGNAL(clicked()), this, SLOT(pickColor()));
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

void Sidebar::logMeshStatus()
{
   //logger->addItem(mesh->meshEntity->status());

//    if (mesh->meshEntity->status() == Qt3DRender::QMesh::Ready)
//        logger->addItem("Mesh status: READY");
//    else if (mesh->meshEntity->status() == Qt3DRender::QMesh::None)
//        logger->addItem("Mesh status: NONE");
//    else if (mesh->meshEntity->status() == Qt3DRender::QMesh::Loading)
//        logger->addItem("Mesh status: LOADING");
//    else
//        logger->addItem("Mesh status: ERROR");


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


