QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH = /home/bryan/Documents/boost_1_73_0
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    jsoncpp.cpp \
    Node.cpp \
    List.cpp \
    GarbageCollector.cpp \
    server.cpp

HEADERS += \
    json.h \
    json-forwards.h \
    Node.h \
    List.h \
    GarbageCollector.h \
    server.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Downloads/hashlibpp_0_3_4/hashlib2plus/trunk/src/release/ -lhl++
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Downloads/hashlibpp_0_3_4/hashlib2plus/trunk/src/debug/ -lhl++
else:unix: LIBS += -L$$PWD/../../../Downloads/hashlibpp_0_3_4/hashlib2plus/trunk/src/ -lhl++

INCLUDEPATH += $$PWD/../../../Downloads/hashlibpp_0_3_4/hashlib2plus/trunk/src
DEPENDPATH += $$PWD/../../../Downloads/hashlibpp_0_3_4/hashlib2plus/trunk/src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../Downloads/hashlibpp_0_3_4/hashlib2plus/trunk/src/release/libhl++.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../Downloads/hashlibpp_0_3_4/hashlib2plus/trunk/src/debug/libhl++.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../Downloads/hashlibpp_0_3_4/hashlib2plus/trunk/src/release/hl++.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../Downloads/hashlibpp_0_3_4/hashlib2plus/trunk/src/debug/hl++.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../Downloads/hashlibpp_0_3_4/hashlib2plus/trunk/src/libhl++.a
