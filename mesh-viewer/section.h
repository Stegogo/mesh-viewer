#ifndef SECTION_H
#define SECTION_H

#include <QGridLayout>              // for layout
#include <QFrame>                   // for animation
#include <QParallelAnimationGroup>  // for animation
#include <QScrollArea>              // scroll area
#include <QToolButton>              // for expand button
#include <QWidget>                  // inherit

//================================================
// SECTION CLASS
// Collapsable section for sidebar
//================================================

class Section : public QWidget
{
    Q_OBJECT

public:
    static const int DEFAULT_DURATION = 0;
    explicit Section(const QString& title = "", const int animationDuration = DEFAULT_DURATION, QWidget* parent = 0);

    void setContentLayout(QLayout& contentLayout);
    void setTitle(QString title);
    void updateHeights();

public slots:
    void toggle(bool collapsed);

private:
    QGridLayout *mainLayout;
    QToolButton *toggleButton;
    QFrame *headerLine;
    QParallelAnimationGroup *toggleAnimation;
    QScrollArea *contentArea;

    int animationDuration;
    int collapsedHeight;

    bool isExpanded = false;
};


#endif // SECTION_H
