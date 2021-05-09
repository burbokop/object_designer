
QT += core-private

include(klibcore/klibcore.pro)
DEFINES += KLIBCORE_USE_LIBRARY
DEFINES += KLIBCORE_USE_EXTENDED_META_SYSTEM

SOURCES += \
    src/lib/__kdynamicobject.cpp \
    src/lib/dynamicobject/formulaparser.cpp \
    src/lib/dynamicobject/jsonconfiguratedworker.cpp \
    src/lib/dynamicobject/kdynamicobject.cpp \
    src/lib/dynamicobject/kvaluesubstitute.cpp \
    src/lib/kdynamicobjectlinker.cpp \
    src/sea/acousticantenna.cpp \
    src/sea/antenarotor.cpp \
    src/appcore.cpp \
    src/client1.cpp \
    src/client2.cpp \
    src/lib/kobjectlifetracker.cpp \
    src/lib/kobjectmap.cpp \
    src/lib/kpropertyview.cpp \
    src/lib/mousespy.cpp \
    src/lib/propertyintersector.cpp \
    src/main.cpp \
    src/sea/kcustomobject.cpp \
    src/sea/pdfwriter.cpp \
    src/sea/seaenvironment.cpp \
    src/sea/vessel.cpp \
    src/simplenegot.cpp \
    src/utility/beamtubeeffect.cpp \
    src/utility/hardwareviewermodel.cpp \
    src/utility/linemonitor.cpp \
    src/utility/rppainter.cpp


HEADERS += \
    src/lib/__kdynamicobject.h \
    src/lib/dynamicobject/formulaparser.h \
    src/lib/dynamicobject/jsonconfiguratedworker.h \
    src/lib/dynamicobject/kdynamicobject.h \
    src/lib/dynamicobject/kvaluesubstitute.h \
    src/lib/kdynamicobjectlinker.h \
    src/sea/acousticantenna.h \
    src/sea/antenarotor.h \
    src/appcore.h \
    src/client1.h \
    src/client2.h \
    src/lib/kobjectlifetracker.h \
    src/lib/kobjectmap.h \
    src/lib/kpropertyview.h \
    src/lib/mousespy.h \
    src/lib/propertyintersector.h \
    src/sea/kcustomobject.h \
    src/sea/pdfwriter.h \
    src/sea/seaenvironment.h \
    src/sea/vessel.h \
    src/simplenegot.h \
    src/utility/beamtubeeffect.h \
    src/utility/hardwareviewermodel.h \
    src/utility/linemonitor.h \
    src/utility/rppainter.h


RESOURCES += \
    qml.qrc
