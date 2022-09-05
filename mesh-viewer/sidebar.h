#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <QColor>
#include <QPixmap>
#include <QPushButton>
#include "mesh.h"

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

private slots:
    void pickColor();
private:
    //QVBoxLayout *m_layout;
    QVBoxLayout *m_layout;

    QColor lightColor;
    QColor diffuseColor;
    QColor ambientColor;

    QPushButton * lightColorButton;
    QPushButton * diffuseColorButton;
    QPushButton * ambientColorButton;

    QPalette lightPallete;
    QPalette diffusePallete;
    QPalette ambientPallete;

    Mesh *mesh;
};

#endif // SIDEBAR_H
