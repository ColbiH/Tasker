QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FileIO.cpp \
    main.cpp \
    old_main.cpp \
    task.cpp \
    task_sorting.cpp \
    tasker.cpp \
    usermodel.cpp

HEADERS += \
    FileIO.h \
    task.h \
    task_sorting.h \
    tasker.h \
    usermodel.h

FORMS += \
    tasker.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Resources/tasks.tsk

