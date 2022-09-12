#ifndef SIDEBAR_H
#define SIDEBAR_H

#include "mesh.h"
#include "view3d.h"
#include <QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <QColor>
#include <QPixmap>
#include <QPushButton>
#include <QSlider>

//================================================
// SIDEBAR CLASS
// Sidebar layout containing view & geometry config
//================================================


class Sidebar : public QWidget
{
    Q_OBJECT
public:
    explicit Sidebar(QWidget *parent = nullptr);

    QListWidget *logger;

    const QColor &getLightColor() const;
    const QColor &getDiffuseColor() const;
    const QColor &getAmbientColor() const;
    const QColor &getWireframeColor() const;

    void setMesh(Mesh *newMesh);
    void setView(View3D *newView);

    Mesh *getMesh() const;
    const QColor &getSpecularColor() const;

private slots:
    void pickColor();
    void pickLightMode();
    void setLightIntensity();
    void setLineWidth();
private:
    QVBoxLayout *m_layout;

    QColor lightColor;
    QColor diffuseColor;
    QColor ambientColor;
    QColor specularColor;
    QColor wireframeColor;

    QPushButton * shadeFlatButton;
    QPushButton * shadeSmoothButton;
    QPushButton * lightColorButton;
    QPushButton * diffuseColorButton;
    QPushButton * ambientColorButton;
    QPushButton * specularColorButton;
    QPushButton * wireframeColorButton;

    QPalette lightPallete;
    QPalette diffusePallete;
    QPalette ambientPallete;
    QPalette specularPallete;
    QPalette wireframePallete;

    QSlider * sliderLight;
    QSlider * sliderLine;

    Mesh *mesh;
    View3D *view;
};

#endif // SIDEBAR_H
