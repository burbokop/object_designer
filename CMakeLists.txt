cmake_minimum_required(VERSION 3.16)

project(object_designer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_LIST_DIR})

include(klibcore/klibcore.cmake)

add_definitions(-DKLIBCORE_USE_EXTENDED_META_SYSTEM)

find_package(Qt5 COMPONENTS
    Core
    Quick
    Multimedia
    Widgets
    Test
    Qml
    REQUIRED
    )



add_executable(object_designer
    src/utility/serialization.cpp
    src/utility/serialization.h
    src/lib/__kdynamicobject.cpp
    src/lib/dynamicobject/formulaparser.cpp
    src/lib/dynamicobject/jsonconfiguratedworker.cpp
    src/lib/dynamicobject/kdynamicobject.cpp
    src/lib/dynamicobject/kvaluesubstitute.cpp
    src/lib/kdynamicobjectlinker.cpp
    src/sea/acousticantenna.cpp
    src/sea/antenarotor.cpp
    src/appcore.cpp
    src/client1.cpp
    src/client2.cpp
    src/lib/kobjectlifetracker.cpp
    src/lib/kobjectmap.cpp
    src/lib/kpropertyview.cpp
    src/lib/mousespy.cpp
    src/lib/propertyintersector.cpp
    src/main.cpp
    src/sea/kcustomobject.cpp
    src/sea/pdfwriter.cpp
    src/sea/seaenvironment.cpp
    src/sea/vessel.cpp
    src/simplenegot.cpp
    src/utility/beamtubeeffect.cpp
    src/utility/hardwareviewermodel.cpp
    src/utility/linemonitor.cpp
    src/utility/rppainter.cpp
    src/lib/__kdynamicobject.h
    src/lib/dynamicobject/formulaparser.h
    src/lib/dynamicobject/jsonconfiguratedworker.h
    src/lib/dynamicobject/kdynamicobject.h
    src/lib/dynamicobject/kvaluesubstitute.h
    src/lib/kdynamicobjectlinker.h
    src/sea/acousticantenna.h
    src/sea/antenarotor.h
    src/appcore.h
    src/client1.h
    src/client2.h
    src/lib/kobjectlifetracker.h
    src/lib/kobjectmap.h
    src/lib/kpropertyview.h
    src/lib/mousespy.h
    src/lib/propertyintersector.h
    src/sea/kcustomobject.h
    src/sea/pdfwriter.h
    src/sea/seaenvironment.h
    src/sea/vessel.h
    src/simplenegot.h
    src/utility/beamtubeeffect.h
    src/utility/hardwareviewermodel.h
    src/utility/linemonitor.h
    src/utility/rppainter.h

    resources.qrc
    )

include_directories(object_designer PRIVATE ${Qt5Core_OWN_PRIVATE_INCLUDE_DIRS})


target_link_libraries(object_designer
    klibcore
    Qt5::Quick
    Qt5::Multimedia
    Qt5::Widgets
    Qt5::Test
    Qt5::Qml
    )
