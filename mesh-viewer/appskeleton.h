#ifndef APPSKELETON_H
#define APPSKELETON_H

#include <QApplication>
#include <QUrl>
#include <QMainWindow>

class AppSkeleton : public QMainWindow
{
    Q_OBJECT
public:
    explicit AppSkeleton(QWidget *parent = nullptr);

private:
    QPixmap newFilePix;
    QPixmap openFilePix;
    QPixmap quitPix;

    void openFileDialog();
};

#endif // APPSKELETON_H
