TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lavcodec
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lavcodec

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lavutil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lavutil


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lavdevice
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lavdevice

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lavfilter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lavfilter

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lavformat
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lavformat

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lswscale
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lswscale

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lswresample
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lswresample

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

HEADERS += \
    wrapper.h

