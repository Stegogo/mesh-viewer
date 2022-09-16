#include "appskeleton.h"
#include "camcontroller.h"
#include "view3d.h"
#include "sidebar.h"

#include <Qt3DExtras/qforwardrenderer.h>        // for FrameGraph
#include <QSplitter>                            // for sidebar splitter
#include <QSizeGrip>                            // for resizing the sidebar

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/img/meshlogo.ico"));

    AppSkeleton mw;

    // Setting up windows and widgets
    View3D *view = new View3D();
    mw.setView(view);
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    QWidget *container = QWidget::createWindowContainer(view);
    QWidget *widget = new QWidget;

    // Setting up sidebar
    Sidebar *sidebar = new Sidebar(widget);
    mw.setSidebar(sidebar);
    sidebar->setMesh(view->getMesh());
    sidebar->setView(view);

    // Configuring layouts
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    view->setWidget(container);
    vLayout->addWidget(sidebar);

    // Configuring camera
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(40.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 400.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

     // Setting camera controller
    CamController * camController = new CamController(view->getMesh()->rootEntity);
    camController->setCamera(camera);

    // Setting a spliiter for adjusting the sidebar size
    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(widget);
    splitter->addWidget(sidebar);

    // Set the initial sizes for QSplitter widgets
    splitter->setSizes(QList<int>{500, 200});

    view->setCamera(camera);
    view->setRootEntity(view->getMesh()->rootEntity);

    mw.setWindowTitle(QStringLiteral("MeshView"));
    mw.setCentralWidget(splitter);
    mw.show();
    mw.resize(900, 700);
    return a.exec();
}

