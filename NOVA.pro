QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    door.cpp \
    main.cpp \
    character.cpp \
    classicboss.cpp \
    companion.cpp \
    finalboss.cpp \
    flashbackobject.cpp \
    game.cpp \
    launchmenu.cpp \
    level.cpp \
    gui.cpp \
    maincharacter.cpp \
    obstacle.cpp \
    optionsmenu.cpp \
    pausemenu.cpp \
    piece.cpp \
    shortscope.cpp

HEADERS += \
    character.h \
    classicboss.h \
    companion.h \
    door.h \
    finalboss.h \
    flashbackobject.h \
    game.h \
    launchmenu.h \
    level.h \
    gui.h \
    maincharacter.h \
    obstacle.h \
    optionsmenu.h \
    pausemenu.h \
    piece.h \
    shortscope.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
