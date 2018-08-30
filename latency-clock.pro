TARGET = latencyclock
TEMPLATE = lib

HEADERS += \
        gsttimeoverlayparse.h \
        gsttimestampoverlay.h

SOURCES += \
        gsttimeoverlayparse.cpp \
        gsttimestampoverlay.cpp \
        plugin.cpp


#LIBS
CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-1.0 gstreamer-video-1.0
