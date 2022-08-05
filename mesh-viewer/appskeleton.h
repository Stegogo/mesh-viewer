#ifndef APPSKELETON_H
#define APPSKELETON_H

#include <QApplication>
#include <QMainWindow>

class AppSkeleton : public QMainWindow
{
    Q_OBJECT
public:
    explicit AppSkeleton(QWidget *parent = nullptr);
};

#endif // APPSKELETON_H
