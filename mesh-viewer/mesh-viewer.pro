QT += core gui multimedia 3dcore 3drender 3dinput 3dquick qml quick 3dquickextras datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appskeleton.cpp \
    camcontroller.cpp \
    customeffect.cpp \
    main.cpp \
    mesh.cpp \
    section.cpp \
    sidebar.cpp \
    view3d.cpp

HEADERS += \
    appskeleton.h \
    camcontroller.h \
    customeffect.h \
    mesh.h \
    section.h \
    sidebar.h \
    view3d.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img/img.qrc \
    img/shaders.qrc

DISTFILES +=
