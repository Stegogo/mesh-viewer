#include "captionwidget.h"
#include <QDebug>
#include <QEvent>
#include <QResizeEvent>

CaptionWidget::CaptionWidget(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);

    setNewParent();
}

void CaptionWidget::setNewParent()
{
    if(!parent())
        return;
    parent()->installEventFilter(this);
    raise();
}

//------------------------
// Catches resize and child events from the parent widget
bool CaptionWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == parent())
    {
    if (event->type() == QEvent::Resize)
        resize(static_cast<QResizeEvent*>(event)->size());
    else if (event->type() == QEvent::ChildAdded)
        raise();
    }
    return QWidget::eventFilter(obj, event);
}

//------------------------
// Tracks parent widget changes
bool CaptionWidget::event(QEvent *event)
{
    switch (event->type())
    {
    default:
        break;
    case QEvent::ParentAboutToChange:
        if (parent())
            parent()->removeEventFilter(this);
        break;
    case QEvent::ParentChange:
        setNewParent();
        break;
//    case QEvent::Move:
//        if (parent())
//            mapFromParent(rect().topLeft());
//        else
//            mapFromGlobal(rect().topLeft());
//        break;
    }

    return QWidget::event(event);
}

void CaptionWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QString text = "あああああああ";
    qDebug() << "あああああああ";
    QFontMetrics metrics(p.font());
    resize(metrics.size(0, text));
    p.drawText(rect(), Qt::AlignCenter, text);
}
