QT += core gui network

INCLUDEPATH += ../common/

SOURCES += \
    ../common/cwidgettxrx.cpp \
    ../common/cclientwidget.cpp \
    ../common/cclientauth.cpp \
    ../common/cclient.cpp \
    swindowserverview.cpp \
    sserver.cpp \
    sgate.cpp \
    scontentsession.cpp \
    schatroom.cpp \
    main.cpp \
    ../common/ccontentchannel.cpp \
    ../common/cchanneluser.cpp \
    ../common/cchannelserver.cpp \
    ../common/cchannelsession.cpp \
    ../common/cchannelparser.cpp \
    ssessionmanager.cpp \
    susermanager.cpp \
    ../common/csessioninfo.cpp \
    ../common/cchatmsg.cpp \
    ../common/cchatinfo.cpp \
    swindowclientinfo.cpp \
    sgatewidget.cpp \
    ../common/cuser.cpp \
    ../common/cfileinfo.cpp \
    ../common/cpadinfo.cpp \
    ../common/cusersinfolist.cpp \
    ../common/cbyteaux.cpp \
    ../common/cpadsinfolist.cpp \
    slivepad.cpp \
    sproject.cpp \
    ../common/cproject.cpp \
    ../common/cfile.cpp \
    ../common/cprojectsnapshot.cpp \
    ../common/cfilewhistory.cpp \
    ../common/cfilechanges.cpp

HEADERS += \
    ../common/cwidgettxrx.h \
    ../common/cclientwidget.h \
    ../common/cclientauth.h \
    ../common/cclient.h \
    swindowserverview.h \
    sserver.h \
    sgate.h \
    scontentsession.h \
    schatroom.h \
    ../common/ccontentchannel.h \
    ../common/cchanneluser.h \
    ../common/cchannelserver.h \
    ../common/cchannelsession.h \
    ../common/cchannelparser.h \
    ssessionmanager.h \
    susermanager.h \
    ../common/csessioninfo.h \
    ../common/cchatmsg.h \
    ../common/cchatinfo.h \
    swindowclientinfo.h \
    sgatewidget.h \
    ../common/cuser.h \
    ../common/cfileinfo.h \
    ../common/cpadinfo.h \
    ../common/cusersinfolist.h \
    ../common/cbyteaux.h \
    ../common/cpadsinfolist.h \
    slivepad.h \
    sproject.h \
    ../common/cproject.h \
    ../common/cfile.h \
    ../common/cprojectsnapshot.h \
    ../common/cfilewhistory.h \
    ../common/cfilechanges.h

FORMS += \
    swindowserverview.ui \
    swindowclientinfo.ui \
    sgatewidget.ui

OTHER_FILES += \
    android/version.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-ru/strings.xml \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/res/drawable-mdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable/icon.png \
    android/res/drawable/logo.png \
    android/res/drawable-hdpi/icon.png

RESOURCES += \
    ../common/resources.qrc
