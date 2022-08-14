#ifndef CAPTIONWIDGET_H
#define CAPTIONWIDGET_H

#include <QWidget>
#include <QPainter>

//================================================
// CAPTION WIDGET CLASS
// Manages 2D paint events;
// Transparent widget that overlays VIEW 3D view
//================================================

class CaptionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CaptionWidget(QWidget *parent = nullptr);

    void setNewParent();

protected:
    void paintEvent(QPaintEvent *event) override;
    // void drawLines(QPainter *qp);
    bool eventFilter(QObject * obj, QEvent * ev) override;
    bool event(QEvent* ev) override;
    void widgetSizeMove();
signals:

};

#endif // CAPTIONWIDGET_H
