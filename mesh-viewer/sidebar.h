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

    void setMesh(Mesh *newMesh);

    Mesh *getMesh() const;

    void setView(View3D *newView);

private slots:
    void pickColor();
    void pickLightMode();
    void setLightIntensity();
private:
    QVBoxLayout *m_layout;

    QColor lightColor;
    QColor diffuseColor;
    QColor ambientColor;

    QPushButton * lightAsIsButton;
    QPushButton * lightFollowCameraButton;
    QPushButton * lightColorButton;
    QPushButton * diffuseColorButton;
    QPushButton * ambientColorButton;

    QPalette lightPallete;
    QPalette diffusePallete;
    QPalette ambientPallete;

    QSlider * slider;

    Mesh *mesh;
    View3D *view;
};

#endif // SIDEBAR_H
